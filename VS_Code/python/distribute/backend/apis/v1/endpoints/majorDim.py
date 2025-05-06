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

majorDim_router = APIRouter()


@majorDim_router.get("/scores/major/chart")
async def get_major_chart(
    db: Session = Depends(get_db),
    redis_store: Redis = Depends(course_cache),
):
    """
    专业维度图标

    :param queryItem:
    :param db:
    :param redis_store:
    :return: [
        {
            "major": "BD",
            "gradeNameList":[
                "大数据18级",
                "大数据19级",
            ]
            ,
            "classNameList": [
                "卓越\n1801",
                "ACM1801",
                "计科\n1801",
            ],
            "failedNum": [
                0,
                0,
                3
            ],
            "failedRate": [
                0.0,
                0.0,
                11.0
            ]
        }
    ]
    """
    key = "major_chart"
    sqlState = (
        db.query(models.ResultReadState)
        .filter(models.ResultReadState.key == key)
        .first()
    )
    redisState = await redis_store.exists(key)
    if (not sqlState) or redisState == 0:
        if not sqlState:  # 更新数据
            ret = []
            # 找到四个年级
            grade_class_info = await get_each_grade_class_number(db, redis_store)
            # print("get_class_chart_by_term:{}".format(grade_class_info))
            majorList = await get_major_list(db)
            for major in majorList:
                if str(major) == "ALL":
                    continue
                tmpDict = {
                    "major": str(major),
                    "gradeNameList": [],
                    "gradeFailedNum": [],
                    "gradeFailedRate": [],
                    "gradeTotalNum": [],
                    "classNameList": [],
                    "failedNum": [],  # 挂科人数
                    "failedRate": [],
                    "totalNum": [],  # 各班总人数
                    "showLabel": [],
                }

                for grade in grade_class_info["grade"].keys():
                    if grade_class_info["major"][str(major)][str(grade)] == 0:
                        continue

                    gradeRes = (
                        db.query(models.Scores)
                        .filter(
                            models.Scores.failed == 1,
                            models.Scores.grade == grade,
                            models.Scores.major == major,
                        )
                        .with_entities(models.Scores.stuID)
                        .distinct()
                        .all()
                    )

                    tmpDict["gradeNameList"].append(
                        str(major) + "\n" + str(grade) + "级"
                    )
                    tmpDict["gradeFailedNum"].append(len(gradeRes))
                    tmpDict["gradeTotalNum"].append(
                        grade_class_info["major"][str(major)][str(grade)]
                    )
                    tmpDict["gradeFailedRate"].append(
                        round(
                            tmpDict["gradeFailedNum"][-1]
                            / tmpDict["gradeTotalNum"][-1]
                            * 100.0,
                            2,
                        )
                    )

                    for term in ["11", "12", "21", "22", "31", "32", "41", "42"]:
                        totalRes = (
                            db.query(models.Scores)
                            .filter(
                                models.Scores.grade == grade,
                                models.Scores.term == term,
                                models.Scores.major == major,
                            )
                            .with_entities(models.Scores.stuID)
                            .distinct()
                            .all()
                        )

                        failedRes = (
                            db.query(models.Scores)
                            .filter(
                                models.Scores.failed == 1,
                                models.Scores.grade == grade,
                                models.Scores.term == term,
                                models.Scores.major == major,
                            )
                            .with_entities(models.Scores.stuID)
                            .distinct()
                            .all()
                        )

                        if len(totalRes) != 0:
                            tmpDict["classNameList"].append(
                                str(
                                    str(major)
                                    + "\n"
                                    + str(grade)
                                    + "级"
                                    + "\nY"
                                    + term[0]
                                    + "S"
                                    + term[1]
                                )
                            )
                            tmpDict["failedNum"].append(len(failedRes))
                            tmpDict["failedRate"].append(
                                round(len(failedRes) / len(totalRes) * 100.0, 2)
                            )
                            tmpDict["totalNum"].append(len(totalRes))
                            tmpDict["showLabel"].append(1 if term == "11" else 0)

                # 修改班级名
                for i in range(len(tmpDict["gradeNameList"])):
                    tmp_className = tmpDict["gradeNameList"][i]
                    tmp_className = tmp_className.replace("CS", "计科")
                    tmp_className = tmp_className.replace("BSB", "本硕博(启明)")
                    tmp_className = tmp_className.replace("BD", "大数据")
                    tmp_className = tmp_className.replace("IOT", "物联网")
                    tmp_className = tmp_className.replace("IST", "智能")
                    tmp_className = tmp_className.replace("ZY", "卓越(创新)")
                    tmp_className = tmp_className.replace("XJ", "校交")
                    tmpDict["gradeNameList"][i] = tmp_className

                for i in range(len(tmpDict["classNameList"])):
                    tmp_className = tmpDict["classNameList"][i]
                    tmp_className = tmp_className.replace("CS", "计科")
                    tmp_className = tmp_className.replace("BSB", "本硕博(启明)")
                    tmp_className = tmp_className.replace("BD", "大数据")
                    tmp_className = tmp_className.replace("IOT", "物联网")
                    tmp_className = tmp_className.replace("IST", "智能")
                    tmp_className = tmp_className.replace("ZY", "卓越(创新)")
                    tmp_className = tmp_className.replace("XJ", "校交")
                    tmpDict["classNameList"][i] = tmp_className

                if tmpDict["classNameList"] != []:
                    ret.append(tmpDict)

            if len(ret) != 0:
                # 将计算好的数据写入数据库
                for majorItem in ret:
                    majorItemQuery = (
                        db.query(models.MajorChart)
                        .filter(models.MajorChart.major == str(majorItem["major"]))
                        .first()
                    )
                    # print("="*50)
                    # print(majorItemQuery)
                    if majorItemQuery:
                        db.query(models.MajorChart).filter(
                            models.MajorChart.major == str(majorItem["major"])
                        ).delete()
                        db.commit()
                    # print("将 班级维度的表数据计算 结果存入数据库 ...")
                    majorItemInsert = models.MajorChart(
                        major=str(majorItem["major"]),
                        gradeNameList=str(majorItem["gradeNameList"]),
                        gradeFailedNum=str(majorItem["gradeFailedNum"]),
                        gradeFailedRate=str(majorItem["gradeFailedRate"]),
                        gradeTotalNum=str(majorItem["gradeTotalNum"]),
                        classNameList=str(majorItem["classNameList"]),
                        failedNum=str(majorItem["failedNum"]),
                        failedRate=str(majorItem["failedRate"]),
                        totalNum=str(majorItem["totalNum"]),
                        showLabel=str(majorItem["showLabel"]),
                    )
                    db.add(majorItemInsert)
                    db.commit()
                    db.refresh(majorItemInsert)
                state_insert = models.ResultReadState(key=key)
                db.add(state_insert)
                db.commit()
                db.refresh(state_insert)
            else:
                return Response400(
                    msg="没有查询到相关数据，请检查查询关键字 or 数据库数据是否为空"
                )

        else:  # 直接读取已经计算好的数据
            retDb: list[models.MajorChart] = db.query(models.MajorChart).all()
            ret = []
            for dbItem in retDb:
                ret.append(
                    {
                        "major": dbItem.major,
                        "gradeNameList": eval(dbItem.gradeNameList),
                        "gradeFailedNum": eval(dbItem.gradeFailedNum),
                        "gradeFailedRate": eval(dbItem.gradeFailedRate),
                        "gradeTotalNum": eval(dbItem.gradeTotalNum),
                        "classNameList": eval(dbItem.classNameList),
                        "failedNum": eval(dbItem.failedNum),
                        "failedRate": eval(dbItem.failedRate),
                        "totalNum": eval(dbItem.totalNum),
                        "showLabel": eval(dbItem.showLabel),
                    }
                )
        if len(ret) != 0:
            # 将数据写入 redis
            await redis_store.setex(
                key,
                config.FAILED_STUID_INFO_REDIS_CACHE_EXPIRES,
                json.dumps(ret, ensure_ascii=False),
            )
        else:
            return Response400(
                data="中间结果数据库中暂时无数据，请在文件上传页面切换读取数据方式为从原始数据读取之后再请求"
            )
    else:
        ret = json.loads(await redis_store.get(key))

    return Response200(data=ret)
