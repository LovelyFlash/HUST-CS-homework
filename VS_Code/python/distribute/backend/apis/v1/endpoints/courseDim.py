import json
import logging
import typing as t
import os

from fastapi import APIRouter, Request, Response, Depends, status, HTTPException
from aioredis import Redis
from sqlalchemy.orm import Session
from sqlalchemy.sql import text
from sqlalchemy import distinct, and_, func, create_engine
import pandas as pd
from starlette.responses import FileResponse

from apis.v1.endpoints.commonCourse import (
    get_each_grade_class_number,
    get_lower_course_name,
    get_major_list,
)
from database.session import get_db
import models
import schemas
from schemas.basic import Response200, Response400
from database.redis import course_cache
from core.config import config
from utils.common import to_pinyin, create_form
import re

courseDim_router = APIRouter()


@courseDim_router.post("/scores/courses")
async def get_coursers_by_term_pass(
    queryItem: schemas.ClassQuery,
    db: Session = Depends(get_db),
    redis_store: Redis = Depends(course_cache),
):
    """
    通过学期获得该学期课程的考试通过情况
    :param queryItem:
    :param db:
    :param redis_store:
    :return:
    [
        {
            "id": "term21",
            "term": "11",
            "courseName": "大学物理（二）",
            "major": "ALL" | "CS"
            "failed_nums": {
                "18":29,
                "19":12
            },
            "gradeDistribute": {
                "18": {
                "0-59": 12,
                "60-69": 71,
                "70-79": 118,
                "80-89": 157,
                "90-100": 48
                },
                "19": {
                },
            },
            "pass_rate": [
                97.0,
                96.0,
                97.0,
                100.0
            ],
            "failStudentsList":[
                ["年级","班级","姓名"]
            ],
            "sumFailedNums": 100
        }
    ]
    """
    term = int(queryItem.term)
    key = "course_by_term_" + str(term)
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
            # 2. 四个grade
            gradeList = grade_class_info["grade"].keys()
            # 找到所有专业
            majorList = await get_major_list(db)
            # 1.获取第 term 学期的所有课程
            courseNameList = [
                courseName[0]
                for courseName in db.query(models.Courses)
                .filter(models.Courses.term == term)
                .with_entities(models.Courses.courseName)
                .distinct()
                .all()
            ]
            low_course_name_list = await get_lower_course_name(
                term, gradeList, db, redis_store
            )
            courseNameList = [
                courseName
                for courseName in courseNameList
                if courseName not in config.NOT_SHOW_COURSE_NAME
            ]
            courseNameList = sorted(courseNameList, key=to_pinyin)
            print("=" * 50)
            print(courseNameList)
            for courseName in courseNameList:
                failedStudentList = []
                failedStu_sql: list[models.Scores] = (
                    db.query(models.Scores)
                    .filter(
                        models.Scores.courseName == courseName, models.Scores.score < 60
                    )
                    .order_by(models.Scores.stuID)
                    .distinct()
                    .all()
                )
                for row in failedStu_sql:
                    student: models.Students = (
                        db.query(models.Students)
                        .filter(models.Students.stuID == row.stuID)
                        .first()
                    )
                    # todo
                    failedStudentList.append(
                        [student.stuClass, row.stuID, student.stuName, row.score]
                    )
                for major in majorList:
                    tmpDict = {
                        "id": "term" + str(term),
                        "term": str(term),
                        "courseName": courseName,
                        "major": str(major),
                        "failed_nums": {},
                        "gradeDistribute": {},
                        "pass_rate": {},
                        "failStudentsList": failedStudentList,
                        "sumFailedNums": len(failedStudentList),
                    }
                    # 将term 学期各个年级的数据初始化
                    totalStuNums = {}
                    for grade in gradeList:
                        tmpDict["gradeDistribute"][str(grade)] = {
                            "0-59": 0,
                            "60-69": 0,
                            "70-79": 0,
                            "80-89": 0,
                            "90-100": 0,
                        }
                        tmpDict["failed_nums"][str(grade)] = 0
                        tmpDict["pass_rate"][str(grade)] = 0
                        totalStuNums[str(grade)] = 0
                    # if courseName not in l
                    res = (
                        db.query(models.Scores)
                        .filter(
                            and_(
                                models.Scores.courseName == courseName,
                                models.Scores.term == term,
                            )
                        )
                        .with_entities(
                            models.Scores.grade,
                            models.Scores.score,
                            models.Scores.stuID,
                            models.Scores.major,
                            models.Scores.failed,
                        )
                        .all()
                    )
                    for row in res:
                        if str(major) == "ALL" or str(row[3]) == str(major):
                            totalStuNums[str(row[0])] += 1
                            if row[4] == 1:
                                tmpDict["gradeDistribute"][str(row[0])]["0-59"] += 1
                                tmpDict["failed_nums"][str(row[0])] += 1
                            elif 60 <= row[1] <= 69:
                                tmpDict["gradeDistribute"][str(row[0])]["60-69"] += 1
                            elif 70 <= row[1] <= 79:
                                tmpDict["gradeDistribute"][str(row[0])]["70-79"] += 1
                            elif 80 <= row[1] <= 89:
                                tmpDict["gradeDistribute"][str(row[0])]["80-89"] += 1
                            elif 90 <= row[1] <= 100:
                                tmpDict["gradeDistribute"][str(row[0])]["90-100"] += 1
                    for grade in gradeList:
                        if totalStuNums[str(grade)] != 0:
                            tmpDict["pass_rate"][str(grade)] = round(
                                (
                                    totalStuNums[str(grade)]
                                    - tmpDict["failed_nums"][str(grade)]
                                )
                                / totalStuNums[str(grade)]
                                * 100,
                                2,
                            )
                    sum_students = 0
                    for grade in gradeList:
                        sum_students += sum(
                            tmpDict["gradeDistribute"][str(grade)].values()
                        )
                    if sum_students > config.NUM_STUDENTS_IN_COURSE_COURSE_DIM:
                        # 该课程在 term 学期上的人数要大于 30，才认为该课程在学院的第 term 学期开设
                        ret.append(tmpDict)

            if len(ret) != 0:
                # 将计算好的数据写入数据库
                for courseItem in ret:
                    courseItemInsert = models.CourseByTermTable(
                        id=courseItem["id"],
                        term=courseItem["term"],
                        courseName=courseItem["courseName"],
                        major=courseItem["major"],
                        failed_nums=str(courseItem["failed_nums"]),
                        gradeDistribute=str(courseItem["gradeDistribute"]),
                        pass_rate=str(courseItem["pass_rate"]),
                        failStudentsList=str(courseItem["failStudentsList"]),
                        sumFailedNums=str(courseItem["sumFailedNums"]),
                    )
                    isInTable = (
                        db.query(models.CourseByTermTable)
                        .filter(
                            and_(
                                models.CourseByTermTable.id == courseItem["id"],
                                models.CourseByTermTable.term == courseItem["term"],
                                models.CourseByTermTable.courseName
                                == courseItem["courseName"],
                                models.CourseByTermTable.major == courseItem["major"],
                            )
                        )
                        .first()
                    )
                    if isInTable != None:
                        db.query(models.CourseByTermTable).filter(
                            and_(
                                models.CourseByTermTable.id == courseItem["id"],
                                models.CourseByTermTable.term == courseItem["term"],
                                models.CourseByTermTable.courseName
                                == courseItem["courseName"],
                                models.CourseByTermTable.major == courseItem["major"],
                            )
                        ).delete()
                        db.commit()
                    # print("将 课程维度的表数据计算 结果存入数据库 ...")
                    db.add(courseItemInsert)
                    db.commit()
                    db.refresh(courseItemInsert)
                state_insert = models.ResultReadState(key=key)
                db.add(state_insert)
                db.commit()
                db.refresh(state_insert)
            else:
                return Response400(
                    msg="没有查询到相关数据，请检查查询关键字 or 数据库数据是否为空"
                )
            # print(courseNameList)
        else:
            # 直接读取已经计算好的数据
            ret = []
            retDb = (
                db.query(models.CourseByTermTable)
                .filter(models.CourseByTermTable.term == str(term))
                .all()
            )
            for dbItem in retDb:
                ret.append(
                    {
                        "id": dbItem.id,
                        "term": dbItem.term,
                        "courseName": dbItem.courseName,
                        "major": dbItem.major,
                        "failed_nums": (
                            eval(dbItem.failed_nums)
                            if len(dbItem.failed_nums) != 0
                            else {}
                        ),
                        "gradeDistribute": (
                            eval(dbItem.gradeDistribute)
                            if len(dbItem.gradeDistribute) != 0
                            else {}
                        ),
                        "pass_rate": (
                            eval(dbItem.pass_rate) if len(dbItem.pass_rate) != 0 else {}
                        ),
                        "failStudentsList": (
                            eval(dbItem.failStudentsList)
                            if dbItem.failStudentsList != []
                            else []
                        ),
                        "sumFailedNums": int(dbItem.sumFailedNums),
                    }
                )
        if len(ret) != 0:
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


@courseDim_router.post("/scores/courses/download")
async def downFailedStudent(
    courseItem: schemas.CourseFailedDownload,
    db: Session = Depends(get_db),
    redis_store: Redis = Depends(course_cache),
):
    """
    通过学期获得该学期课程的考试通过情况
    :param queryItem:
    :param db:
    :param redis_store:
    :return:
    返回如下字段的 excel文件
    ["序号", "年级","班级", "学号", "姓名","开课学期","成绩"]

    """

    try:
        # 参数1：文件的路径 filename：自定义导出的文件名（需要带上格式后缀）
        courseName = str(courseItem.courseName)
        source_dir = "./documents/failedStudentExcel/"
        failed_student_excel_name = "failed_students_" + str(courseName) + ".xlsx"
        # os.path.exists(source_dir+failed_student_excel_name)

        ret: list[models.Scores] = (
            db.query(models.Scores)
            .filter(models.Scores.courseName == courseName, models.Scores.score < 60)
            .distinct()
            .all()
        )
        # todo
        FORM_HEADER = ["序号", "年级","班级", "学号", "姓名","开课学期","成绩"]
        FORM_DATA = []
        index = 1
        for row in ret:
            student: models.Students = (
                db.query(models.Students)
                .filter(models.Students.stuID == row.stuID)
                .first()
            )
            # 班级格式转换
            stu_class = student.stuClass
            if "BD" in stu_class:
                stu_class = "大数据" + stu_class[-4:]
            elif "BSB" in stu_class:
                stu_class = "本硕博" + stu_class[-4:]
            elif "ZY" in stu_class:
                stu_class = "卓越(创新)" + stu_class[-4:]
            elif "IOT" in stu_class:
                stu_class = "物联网" + stu_class[-4:]
            elif "XJ" in stu_class:
                stu_class = "校交" + stu_class[-4:]
            elif "IST" in stu_class:
                stu_class = "智能" + stu_class[-4:]
            elif "TL" in stu_class:
                stu_class = "图灵" + stu_class[-4:]
            elif "CS" in stu_class:
                stu_class = "计算机" + stu_class[-4:]
            
            FORM_DATA.append(
                [index, row.grade, stu_class, row.stuID, student.stuName, row.term, row.score]
            )
            index += 1
        create_form(source_dir + failed_student_excel_name, FORM_DATA, FORM_HEADER)

        if len(ret) == 0:
            # 中间计算表还没计算出来
            return Response400(
                msg="中间结果数据库中暂时无数据，请在文件上传页面切换读取数据方式为从原始数据读取之后再请求"
            )

        return FileResponse(
            path=source_dir + failed_student_excel_name,
            filename=failed_student_excel_name,
        )
    except Exception as e:
        return Response400(msg=str(e))
