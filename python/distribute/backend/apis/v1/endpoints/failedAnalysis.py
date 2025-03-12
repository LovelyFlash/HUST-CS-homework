import json
import logging
import os
import re
import typing as t

from fastapi import (
    APIRouter,
    File,
    UploadFile,
    Request,
    Response,
    Depends,
    status,
    HTTPException,
)
from sqlalchemy.orm import Session
from aioredis import Redis
import pandas as pd

from database.session import get_db
import models
import schemas
from schemas.basic import Response200, Response400
from database.redis import course_cache
from core.config import config


failA_router = APIRouter(tags=["不及格分析"])


@failA_router.post("/students/analysis")
async def get_stuAnalysis(
    request: Request,
    select_Bar: schemas.StuAnalysisBar,
    db=Depends(get_db),
    redis_store: Redis = Depends(course_cache),
):
    """
    获取数据库 stuanalysis 中的信息
    :return:
    """
    select_term_bar = select_Bar.stuTermBar
    select_class_bar = select_Bar.stuClassID
    print("DEBUG getStu: ", select_term_bar, select_class_bar)
    stuAnsInfos = await getStuAnsFromSql(
        db, redis_store, select_term_bar, select_class_bar
    )
    if stuAnsInfos != -1:
        return Response200(data=stuAnsInfos)
    else:
        return Response400(
            code=status.HTTP_404_NOT_FOUND, msg="所选班级信息暂未导入，请导入后操作"
        )


@failA_router.get("/stuclasses")
async def get_classes(
    db: Session = Depends(get_db), redis_store: Redis = Depends(course_cache)
):
    """
    获取班级信息
    :param db:
    :return:
    """
    try:
        # 从缓存中获取数据
        state = await redis_store.exists("class_info")
        if state != 0:
            resp_json = await redis_store.get("class_info")
            if resp_json:
                if isinstance(resp_json, str):
                    resp_json = json.loads(resp_json)
                return Response200(data=resp_json)
        else:
            class_list = (
                db.query(models.Students)
                .with_entities(models.Students.stuClass)
                .distinct()
                .order_by(models.Students.stuClass)
                .all()
            )
            dict_list = []
            i = 1
            for cla in class_list:
                d = {"cls_id": i, "className": cla[0]}
                i += 1
                dict_list.append(d)
            # print(dict_list)
            if len(dict_list) != 0:
                resp_json = json.dumps(dict_list, ensure_ascii=False)
                # 将信息存入 redis
                await redis_store.setex(
                    "class_info", config.CLASS_INFO_REDIS_CACHE_EXPIRES, resp_json
                )

                return Response200(data=dict_list)
            else:
                return Response400(
                    msg="没有查询到相关数据，请检查查询关键字 or 数据库数据是否为空"
                )
    except Exception as e:
        return Response400(
            code=status.HTTP_500_INTERNAL_SERVER_ERROR, msg="发生异常：" + str(e)
        )


async def get_classes_fun(db: Session, redis_store: Redis):
    """
    获取班级信息
    :param db:
    :return:
    """
    try:
        # 从缓存中获取数据
        state = redis_store.exists("class_info")
        if state != 0:
            resp_json = redis_store.get("class_info")
            if resp_json:
                return Response200(data=resp_json)
        else:
            class_list = (
                db.query(models.Students)
                .with_entities(models.Students.stuClass)
                .distinct()
                .order_by(models.Students.stuClass)
                .all()
            )
            dict_list = []
            i = 1
            for cla in class_list:
                d = {"cls_id": i, "className": cla[0]}
                i += 1
                dict_list.append(d)
            # print(dict_list)
            resp_json = json.dumps(dict_list, ensure_ascii=False)
            # 将信息存入 redis
            await redis_store.setex(
                "class_info", config.CLASS_INFO_REDIS_CACHE_EXPIRES, resp_json
            )

            return Response200(data=resp_json)
    except Exception as e:
        return Response400(
            code=status.HTTP_500_INTERNAL_SERVER_ERROR, msg="发生异常：" + str(e)
        )


async def getStuAnsFromSql(
    db: Session, redis_store: Redis, select_term_bar, select_class_bar
):
    """
    根据选择 从数据库中读取信息
    :param select_term_bar: 下拉框选中的学期
    :param select_class_bar: 下拉框中选中的班级
    :return:
    """

    if select_class_bar == "11" and select_term_bar == None:
        # 不是通过select 标签选择的
        term = "11"
        className = await getClass(0, db, redis_store)
    else:
        # select标签内容不为空
        term = select_term_bar
        # index = int(select_class_bar)
        className = str(select_class_bar)
        # className = await getClass(index,db,redis_store)
    print("debug stu analysis: term: {},className: {}".format(term, className))
    try:
        # print("DEBUG getStuAnsFromSql: ",term,className)
        stuClassInStuAn = (
            db.query(models.StuAnalysis)
            .with_entities(models.StuAnalysis.stuClass)
            .distinct()
            .all()
        )
        stuClass_ann_list = []
        # print("len stuClassInStuAn: ",len(stuClassInStuAn))
        for stcla in stuClassInStuAn:
            # print(stcla)
            stuClass_ann_list.append(stcla[0])
        # print("stuAnalysis表中的班级信息: ",stuClass_ann_list)
        if className not in stuClass_ann_list:
            print("班级信息未导入")
            return -1
        stuAnalysisinfos = (
            db.query(models.StuAnalysis)
            .filter(
                models.StuAnalysis.term == term,
                models.StuAnalysis.stuClass == className,
            )
            .all()
        )
        # print("get stuanakysis: ",stuAnalysisinfos)
    except Exception as E:
        logging.error("数据库异常" + str(E))
        return Response400(
            code=status.HTTP_500_INTERNAL_SERVER_ERROR, msg="数据库异常" + str(E)
        )
    stuAna_list = []
    for info in stuAnalysisinfos:
        # print(info.stuID, info.stuName, info.stuType, info.term)
        info = info.to_dic()
        info["failSubjectNameList"] = []
        if info["failSubjectName"]:
            info["failSubjectName"] = info["failSubjectName"].replace("、", ",")
            info["failSubjectName"] = info["failSubjectName"].replace("，", ",")
            info["failSubjectNameList"] = info["failSubjectName"].split(",")
            # print(info["failSubjectName"])
            # print((info["failSubjectNameList"]))

        stuAna_list.append(info)

    return stuAna_list
    # resp_json = json.dumps(stuAna_list,ensure_ascii=False)  # 将一个Python数据结构转换为JSON
    # return resp_json


async def getClass(index, db: Session, redis_store: Redis):
    """
    从redis中查询班级信息，并转换为 str 数据类型
    :param redis_data:
    :param index:
    :return:
    """
    # print(redis_store.get("class_info"))
    state = redis_store.exists("class_info")
    if state == 0:
        await get_classes_fun(db, redis_store)

    data = await redis_store.get("class_info")
    if data and index > 0:
        # 在缓存中存在
        data = str(data, encoding="utf-8")
        data = eval(data)
        return data["data"][int(index - 1)]["className"]
    else:
        # 不在缓存中。从数据库中去查找第一个班级
        try:
            data = (
                db.query(models.Students)
                .with_entities(models.Students.stuClass)
                .distinct()
                .order_by(models.Students.stuClass)
                .first()
            )
            return data[0]
        except Exception as E:
            print("getclass exception:{}".format(str(E)))
            return -1
