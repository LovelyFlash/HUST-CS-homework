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
from .commonCourse import get_each_grade_class_number
import re

classDim_router = APIRouter()


@classDim_router.post("/scores/class/chart")
async def get_class_chart_by_term(
    queryItem: schemas.ClassQuery,
    db: Session = Depends(get_db),
    redis_store: Redis = Depends(course_cache),
):
    """
    班级维度图标

    :param queryItem:
    :param db:
    :param redis_store:
    :return: [
         {
            "term": "11",
            "grade": "18",
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
    term = int(queryItem.term)
    key = "class_by_term_chart_" + str(term)
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
            print("get_class_chart_by_term:{}".format(grade_class_info))
            for grade in grade_class_info["grade"].keys():
                tmpDict = {
                    "classNameList": [],
                    "failedNum": [],  # 挂科人数
                    "failedRate": [],
                    "totalNum": [],  # 各班总人数
                    "grade": str(grade),
                    "term": str(term),
                    "type": 1,
                }
                tmpDictMajor = {
                    "classNameList": [],
                    "failedNum": [],  # 挂科人数
                    "failedRate": [],
                    "totalNum": [],  # 各班总人数
                    "grade": str(grade),
                    "term": str(term),
                    "type": 0,
                }
                count = 0
                lastMajorIndex = 0
                for className in grade_class_info["class_nums_student"][grade]:
                    if (
                        count == 0
                        or re.search(
                            r"[A-Z]+", tmpDict["classNameList"][count - 1]
                        ).group()
                        != re.search(r"[A-Z]+", className).group()
                    ):
                        tmpDictMajor["classNameList"].append(
                            re.search(r"[A-Z]+", className).group()
                        )
                        tmpDictMajor["failedNum"].append(0)
                        tmpDictMajor["failedRate"].append(0)
                        tmpDictMajor["totalNum"].append(0)
                        lastMajorIndex += 1
                    res_class = (
                        db.query(models.Scores)
                        .join(
                            models.Students,
                            models.Scores.stuID == models.Students.stuID,
                            isouter=True,
                        )
                        .filter(
                            and_(
                                models.Students.stuClass == className,
                                models.Scores.term == term,
                                models.Scores.failed == 1,
                            )
                        )
                        .with_entities(models.Scores.stuID)
                        .distinct()
                        .all()
                    )
                    tmpDict["classNameList"].append(className)
                    tmpDict["failedNum"].append(len(res_class))
                    tmpDictMajor["failedNum"][lastMajorIndex - 1] += len(res_class)
                    tmpDict["failedRate"].append(0)
                    tmpDict["totalNum"].append(
                        grade_class_info["class_nums_student"][str(grade)][className]
                    )
                    tmpDictMajor["totalNum"][lastMajorIndex - 1] += grade_class_info[
                        "class_nums_student"
                    ][str(grade)][className]
                    count += 1

                # 计算不及格率，修改班级名
                for i in range(len(tmpDict["classNameList"])):
                    if tmpDict["totalNum"][i] != 0:
                        tmpDict["failedRate"][i] = round(
                            tmpDict["failedNum"][i] / tmpDict["totalNum"][i] * 100, 2
                        )

                    tmp_className = tmpDict["classNameList"][i]
                    if tmp_className == "":
                        continue
                    tmp_className = (
                        re.search(r"[A-Z]+", tmp_className).group()
                        + "\n"
                        + (
                            re.search(r"[0-9]+", tmp_className).group()
                            if re.search(r"[0-9]+", tmp_className) != None
                            else ""
                        )
                    )
                    tmp_className = tmp_className.replace("CS", "计科")
                    tmp_className = tmp_className.replace("BSB", "本硕博(启明)")
                    tmp_className = tmp_className.replace("BD", "大数据")
                    tmp_className = tmp_className.replace("IOT", "物联网")
                    tmp_className = tmp_className.replace("IST", "智能")
                    tmp_className = tmp_className.replace("ZY", "卓越(创新)")
                    tmp_className = tmp_className.replace("XJ", "校交")
                    tmpDict["classNameList"][i] = tmp_className
                if sum(tmpDict["failedNum"]) != 0:
                    ret.append(tmpDict)

                for i in range(len(tmpDictMajor["classNameList"])):
                    if tmpDictMajor["totalNum"][i] != 0:
                        tmpDictMajor["failedRate"][i] = round(
                            tmpDictMajor["failedNum"][i]
                            / tmpDictMajor["totalNum"][i]
                            * 100,
                            2,
                        )

                    tmp_className = tmpDictMajor["classNameList"][i]
                    if tmp_className == "":
                        continue
                    tmp_className = (
                        re.search(r"[A-Z]+", tmp_className).group()
                        + "\n"
                        + (
                            re.search(r"[0-9]+", tmp_className).group()
                            if re.search(r"[0-9]+", tmp_className) != None
                            else ""
                        )
                    )
                    tmp_className = tmp_className.replace("CS", "计科")
                    tmp_className = tmp_className.replace("BSB", "本硕博(启明)")
                    tmp_className = tmp_className.replace("BD", "大数据")
                    tmp_className = tmp_className.replace("IOT", "物联网")
                    tmp_className = tmp_className.replace("IST", "智能")
                    tmp_className = tmp_className.replace("ZY", "卓越(创新)")
                    tmp_className = tmp_className.replace("XJ", "校交")
                    tmpDictMajor["classNameList"][i] = tmp_className
                if sum(tmpDictMajor["failedNum"]) != 0:
                    ret.append(tmpDictMajor)

            if len(ret) != 0:
                # 将计算好的数据写入数据库
                for classItem in ret:
                    classItemQuery = (
                        db.query(models.ClassByTermChart)
                        .filter(
                            and_(
                                models.ClassByTermChart.term == classItem["term"],
                                models.ClassByTermChart.grade
                                == str(classItem["grade"]),
                                models.ClassByTermChart.type == classItem["type"],
                            )
                        )
                        .first()
                    )
                    if classItemQuery:
                        db.query(models.ClassByTermChart).filter(
                            and_(
                                models.ClassByTermChart.term == classItem["term"],
                                models.ClassByTermChart.grade
                                == str(classItem["grade"]),
                                models.ClassByTermChart.type == classItem["type"],
                            )
                        ).delete()
                        db.commit()
                    print("将 班级维度的表数据计算 结果存入数据库 ...")
                    classItemInsert = models.ClassByTermChart(
                        term=classItem["term"],
                        grade=str(classItem["grade"]),
                        classNameList=str(classItem["classNameList"]),
                        failedNum=str(classItem["failedNum"]),
                        failedRate=str(classItem["failedRate"]),
                        totalNum=str(classItem["totalNum"]),
                        type=classItem["type"],
                    )
                    db.add(classItemInsert)
                    db.commit()
                    db.refresh(classItemInsert)
                state_insert = models.ResultReadState(key=key)
                db.add(state_insert)
                db.commit()
                db.refresh(state_insert)

            else:
                return Response400(
                    msg="没有查询到相关数据，请检查查询关键字 or 数据库数据是否为空"
                )

        else:  # 直接读取已经计算好的数据
            retDb = (
                db.query(models.ClassByTermChart)
                .filter(models.ClassByTermChart.term == str(term))
                .all()
            )
            ret = []
            for dbItem in retDb:
                ret.append(
                    {
                        "term": dbItem.term,
                        "grade": dbItem.grade,
                        "classNameList": (
                            eval(dbItem.classNameList)
                            if dbItem.classNameList != ""
                            else []
                        ),
                        "failedNum": (
                            eval(dbItem.failedNum) if dbItem.classNameList != "" else []
                        ),
                        "failedRate": (
                            eval(dbItem.failedRate)
                            if dbItem.classNameList != ""
                            else []
                        ),
                        "totalNum": (
                            eval(dbItem.totalNum) if dbItem.totalNum != "" else []
                        ),
                        "type": dbItem.type,
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
