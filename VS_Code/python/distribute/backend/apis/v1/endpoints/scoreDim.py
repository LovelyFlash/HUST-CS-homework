import json
import logging
import typing as t

from fastapi import APIRouter, Request, Response, Depends, status, HTTPException
from sqlalchemy.orm import Session
from sqlalchemy.sql import text
from sqlalchemy import distinct, and_, func, create_engine
from aioredis import Redis

from database.session import get_db
import models
import schemas
from schemas.basic import Response200, Response400
from database.redis import course_cache
from core.config import config
from .commonCourse import get_each_grade_class_number, get_major_list
import re

scoreDim_router = APIRouter()

@scoreDim_router.post("/scores/score/chart")
async def get_weight_score_chart(
    queryItem: schemas.BaseQuery,
    db: Session = Depends(get_db),
    redis_store: Redis = Depends(course_cache),
):
    term = str(queryItem.term)
    key = "weight_score_by_term_" + str(term)
    sqlState = db.query(models.ResultReadState).filter(models.ResultReadState.key==key).first()
    redisState = await redis_store.exists(key)
    if (not sqlState) or redisState == 0:
        if not sqlState:  # 更新数据
            # 1. 得到一些基本信息（年级人数，班级人数）
            each_grade_class_number = await get_each_grade_class_number(db, redis_store)
            # 2. 四个grade
            gradeList = each_grade_class_number["grade"].keys()
            majorList = await get_major_list(db)

            ret = []
            for grade in gradeList:
                for major in majorList:
                    if major == "ALL":
                        continue
                    res : list[models.WeightScores] = db.query(models.WeightScores).filter(models.WeightScores.term == term, models.WeightScores.grade == grade, models.WeightScores.major == major).order_by(models.WeightScores.score.desc()).distinct().all()
                    result = []
                    for i in range(len(res)):
                        result.append({"Name": res[i].stuName, "ID": res[i].stuID, "Score": res[i].score, "Index": i + 1, "Class": 0})
                        if i == (len(res) + 1) // 2 - 1:
                            result[-1]["Class"] |= 1
                        if i > 1 and result[-2]["Score"] >= 85.0 and result[-1]["Score"] < 85.0:
                            result[-2]["Class"] |= 2
                        
                    if result != []:
                        ret.append({"term": term, "grade": grade, "major": major, "info": result})
            if len(ret) != 0:
                # 将计算好的数据写入数据库
                for item in ret:
                    res = db.query(models.WeightScoreByTerm).filter(models.WeightScoreByTerm.grade==item["grade"], models.WeightScoreByTerm.term==item["term"], models.WeightScoreByTerm.major==item["major"]).first()
                    if res:
                        res.info = str(item["info"])
                        db.commit()
                        db.refresh(res)
                    else:
                        ins_sql = models.WeightScoreByTerm(grade=item["grade"], term=item["term"], major=item["major"], info=str(item["info"]))
                        db.add(ins_sql)
                        db.commit()
                        db.refresh(ins_sql)
            else:
                return Response400(msg="没有查询到相关数据，请检查查询关键字 or 数据库数据是否为空")
            state_insert = models.ResultReadState(key=key)
            db.add(state_insert)
            db.commit()
            db.refresh(state_insert)
        else:
            # 直接读取计算好的数据
            retDb = db.query(models.WeightScoreByTerm).filter(models.WeightScoreByTerm.term == term).all()
            ret = []
            for dbItem in retDb:
                ret.append(
                    {
                        "grade": dbItem.grade,
                        "term": dbItem.term,
                        "major": dbItem.major,
                        "info": eval(dbItem.info) if dbItem.info != '' else [],
                    }
                )
        if(len(ret) != 0):
            # 将数据写入缓存
            await redis_store.setex(key, config.FAILED_STUID_INFO_REDIS_CACHE_EXPIRES, json.dumps(ret, ensure_ascii=False))
        else:
            return Response400(data="中间结果数据库中暂时无数据")
    else:
        ret = json.loads(await redis_store.get(key))

    return Response200(data=ret)
