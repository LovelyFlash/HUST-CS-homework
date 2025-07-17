import json
import logging
import typing as t

from fastapi import APIRouter, Request, Response, Depends,status,HTTPException



from database.session import get_db
import models
import schemas
from schemas.basic import Response200, Response400
from database.redis import course_cache
from core.config import config
from database.curd_ec import (
    ec_get_by_year, ec_getYearList, ec_get_by_grade, ec_get_info_by_grade_year, ec_getGradeList
)
from .commonCourse import get_each_grade_class_number

ec_router = APIRouter()

@ec_router.get("/excellent/flushALL")
async def excellentClassFlushALL(db=Depends(get_db)):
    db.query(models.ResultReadState).filter(models.ResultReadState.key=="excellentStudyClassBar").delete()
    db.query(models.ResultReadState).filter(models.ResultReadState.key=="excellentStudyClassLine").delete()
    db.query(models.ExcellentStudyClass).delete()
    db.commit()
    


@ec_router.post("/excellent/info")
async def add_excellent_class_info(ec_info: schemas.ExcellentStudyClassSchemas, db=Depends(get_db), redis_store=Depends(course_cache)):
    """
    保存当年的优良学分班信息
    {
        "grade":self.grade,
        "year":self.year,
        "totalClassNum":self.totalClassNum,
        "excellentClassNum":self.excellentClassNum
    }
    :return:
    """
    ec_info_old = await ec_get_info_by_grade_year(db,ec_info.grade,ec_info.year)
    if not ec_info_old:
        grade_class_info = await get_each_grade_class_number(db, redis_store)
        db_ec_info = models.ExcellentStudyClass(
            grade=ec_info.grade,
            year=ec_info.year,
            totalClassNum=ec_info.totalClassNum,
            excellentClassNum=ec_info.excellentClassNum,
        )
        db.query(models.ResultReadState).filter(models.ResultReadState.key=="excellentStudyClassBar").delete()
        db.query(models.ResultReadState).filter(models.ResultReadState.key=="excellentStudyClassLine").delete()
        db.add(db_ec_info)
        db.commit()
        db.refresh(db_ec_info)
        return Response200(msg="优良学风班数据插入成功")
    else:
        return Response400(code=status.HTTP_207_MULTI_STATUS,msg="该数据已经在数据库中存在")


@ec_router.get("/excellentInfoBar")
async def get_excellentStudyClass_info_histogram(db=Depends(get_db),redis_store=Depends(course_cache)):
    """
        获取优良学风班的柱状图信息

        :return:
        {
            "2018":{
                "excellentStudyClassNum":12,
                "excellentRate":26%,
            }
        }
        """
    # 先从缓存中读取
    key = "excellentStudyClassBar"
    sqlState = db.query(models.ResultReadState).filter(models.ResultReadState.key==key).first()
    redisState = await redis_store.exists(key)
    if sqlState and redisState != 0:
        try:
            resp_dict = await redis_store.get(key)
            resp_dict = json.loads(resp_dict)
            return Response200(data=resp_dict)
        except Exception as E:
            logging.error("从 redis 读 excellentStudyClassBar 异常 %s" % E)

            return Response400(msg="从 redis 读 异常 %s" % str(E))
    else:
        yearList = await ec_getYearList(db)
        # 从 2018年开始
        resp_data = {}
        # 初始化
        for year in yearList:
            res = await ec_get_by_year(db,year)
            res['excellentRate'] = '{:.2f}'.format((round(res["excellentStudyClassNum"] * 1.0 / res["totalClassNum"], 2) * 100))
            if res["totalClassNum"] > 30:
                resp_data[str(year)] = res
        if not sqlState:
            state_insert = models.ResultReadState(key=key)
            db.add(state_insert)
            db.commit()
            db.refresh(state_insert)

        if len(resp_data) != 0:
            # 写入 redis
            try:
                await redis_store.setex(key, config.FAILED_STUID_INFO_REDIS_CACHE_EXPIRES, json.dumps(resp_data))
            except Exception as E:
                return -1, E
        else:
            return Response400(msg="没有查询到相关数据，请检查查询关键字 or 数据库数据是否为空")


    return Response200(msg="请求成功",data=resp_data)



@ec_router.get("/excellentInfoLine")
async def get_excellentStudyClass_info_line(db=Depends(get_db),redis_store=Depends(course_cache)):
    """
    获取优良学分班的折线图信息
    :return:
    {
        "16":{
            "grade2":28.57%,
            "grade3":42.86%,
            "grade4":57.14%
        }
    }
    """
    # 先从缓存中读取
    key = "excellentStudyClassLine"
    sqlState = db.query(models.ResultReadState).filter(models.ResultReadState.key==key).first()
    redisState = await redis_store.exists(key)
    if sqlState and redisState != 0:
        try:
            resp_dict = await redis_store.get(key)
            resp_dict = json.loads(resp_dict)
            return Response200(data=resp_dict)
        except Exception as E:
            logging.error("从 redis 读 excellentStudyClassLine 异常 %s" % E)
            Response400(msg="从 redis 读 异常 %s" % str(E))
    else:
        yearList = await ec_getGradeList(db)
        resp_data = {}
        for year in yearList:
            grade = year % 2000
            resp_data[str(year)] = await (ec_get_by_grade(db,grade))
        if not sqlState:
            state_insert = models.ResultReadState(key=key)
            db.add(state_insert)
            db.commit()
            db.refresh(state_insert)

        if len(resp_data) != 0:
            # 写入 redis
            try:
                await redis_store.setex(key, config.FAILED_STUID_INFO_REDIS_CACHE_EXPIRES,
                                json.dumps(resp_data))
            except Exception as E:
                print("将 excellentStudyClassLine 写入 redis 异常 ", str(E))
                return -1, E
        else:
            return Response400(msg="没有查询到相关数据，请检查查询关键字 or 数据库数据是否为空")
    return Response200(msg="请求成功",data=resp_data)