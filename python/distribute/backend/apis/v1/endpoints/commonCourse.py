import json
import logging
import typing as t
import re

from fastapi import APIRouter, Request, Response, Depends, status, HTTPException
from sqlalchemy.orm import Session
from sqlalchemy import and_, or_, func
from aioredis import Redis
import difflib

from database.session import get_db
import models
import schemas
from schemas.basic import Response200, Response400
from database.redis import course_cache
from core.config import config


async def get_lower_course_name(term, gradeList, db: Session, redis_store: Redis):
    """
    获取 term 学期 每个grade 的课程数量
    然后将低于 阙值的课程返回
    :param db:
    :return:
    """
    key = "low_course_name_list_" + str(term)
    sqlState = (
        db.query(models.ResultReadState)
        .filter(models.ResultReadState.key == key)
        .first()
    )
    redisState = await redis_store.exists(key)
    if (not sqlState) or redisState == 0:
        ret_dict = {}
        for grade in gradeList:
            low_course_list = (
                db.query(models.Scores)
                .filter(and_(models.Scores.term == term, models.Scores.grade == grade))
                .with_entities(
                    models.Scores.courseName,
                    models.Scores.term,
                    func.count(models.Scores.courseName),
                )
                .group_by(models.Scores.courseName)
                .all()
            )
            res = sorted(low_course_list, key=lambda t: t[2])
            ret_dict[str(grade)] = []
            # 返回低于阙值的课程
            for course in res:
                if course[2] < config.NUM_STUDENTS_IN_COURSE:
                    ret_dict[str(grade)].append(course[0])
        print("low_course_name_list_{}:{}".format(term, ret_dict))
        if not sqlState:
            state_insert = models.ResultReadState(key=key)
            db.add(state_insert)
            db.commit()
            db.refresh(state_insert)
        await redis_store.setex(
            key,
            config.FAILED_STUID_INFO_REDIS_CACHE_EXPIRES,
            json.dumps(ret_dict, ensure_ascii=False),
        )
    else:
        ret_dict = json.loads(await redis_store.get(key))
    return ret_dict


async def get_lower_course_name_by_term_grade(
    term, gradeList, db: Session, redis_store: Redis
):
    """
    获取 term 学期 每个grade 的课程数量
    然后将低于 阙值的课程返回
    :param db:
    :return:
    """
    redis_key = "low_course_name_list_" + str(term)
    state = await redis_store.exists(redis_key)
    if state == 0:
        ret_dict = {}
        for grade in gradeList:
            low_course_list = (
                db.query(models.Scores)
                .filter(and_(models.Scores.term == term, models.Scores.grade == grade))
                .with_entities(
                    models.Scores.courseName,
                    models.Scores.term,
                    func.count(models.Scores.courseName),
                )
                .group_by(models.Scores.courseName)
                .all()
            )
            res = sorted(low_course_list, key=lambda t: t[2])
            ret_dict[str(grade)] = []
            # 返回低于阙值的课程
            for course in res:
                if course[2] < config.NUM_STUDENTS_IN_COURSE:
                    ret_dict[str(grade)].append(course[0])
        print("low_coursename_list_{}:{}".format(term, ret_dict))
        await redis_store.setex(
            redis_key,
            config.FAILED_STUID_INFO_REDIS_CACHE_EXPIRES,
            json.dumps(ret_dict, ensure_ascii=False),
        )
    else:
        ret_dict = json.loads(await redis_store.get(redis_key))
    return ret_dict


async def get_class_list(db: Session):
    """
    获取所有班级信息
    :param db:
    :return:
    """
    res_class = (
        db.query(models.Students)
        .with_entities(models.Students.stuClass)
        .distinct()
        .all()
    )
    class_list = []
    for res in res_class:
        class_list.append(res[0])
    ret = sorted(class_list)
    print("class_list:{}".format(ret))
    return ret


async def get_major_list(db: Session):
    """
    获取所有专业信息
    :param db:
    :return:
    """
    res_major = (
        db.query(models.Students)
        .with_entities(models.Students.stuClass)
        .distinct()
        .all()
    )
    major_list = []
    for res in res_major:
        major_list.append(re.search(r"[A-Z]+", res[0]).group())
    major_list.append("ALL")
    ret = sorted(set(major_list))
    print("major_list:{}".format(ret))
    return ret


async def get_each_grade_class_number(db: Session, redis_store: Redis):
    """

    获取每个年级的总人数
    :return:
    {
        "grade":{
            "17":123,
            "18":134,
            "20":43,
        },
        "major": {
            "ALL": {
                "17":123,
                "18":134,

            },
            "CS": {
            }
        }
        "class_nums_student":{
            "17":{
                'CS1701': 32,
                'CS1707': 30
            },
            "18":{

            }
        }
    }
    """
    key = "grade_class_info"
    sqlState = (
        db.query(models.ResultReadState)
        .filter(models.ResultReadState.key == key)
        .first()
    )
    redisState = await redis_store.exists(key)
    if (not sqlState) or redisState == 0:
        class_list = await get_class_list(db)
        major_list = await get_major_list(db)
        # 先获取各个年级的名称
        dict_grade_list = {}
        dict_grade_list["grade"] = {}
        dict_grade_list["major"] = {}
        dict_grade_list["class_nums_student"] = {}
        dict_nums_student_global = {}  # 存放所有班级的学生数量
        for className in class_list:
            tmpRes = (
                db.query(models.Students)
                .filter(models.Students.stuClass == className)
                .all()
            )
            dict_nums_student_global[className] = len(tmpRes)

        grade_set = set()
        for className in dict_nums_student_global.keys():
            grade_set.add(className[-4:-2])

        # 初始化 grade
        tmp_grade = sorted(grade_set)
        for grade in tmp_grade:
            dict_grade_list["grade"][grade] = 0
            dict_grade_list["class_nums_student"][str(grade)] = {}
        # 初始化每个班级人数为 0

        for grade in grade_set:
            dict_grade_list["class_nums_student"][str(grade)] = {}

        # # 初始化班级信息
        for className in class_list:
            grade = await get_grade(className)
            dict_grade_list["class_nums_student"][str(grade)][className] = 0

        # 调整班级顺序
        for grade in grade_set:
            tmp_class_nums_student_list = dict_grade_list["class_nums_student"][
                grade
            ].keys()
            tmp_class_nums_student_list = sorted(tmp_class_nums_student_list)

            # 计算班级人数
            class_nums_student = {}
            for className in tmp_class_nums_student_list:
                class_nums_student[className] = dict_nums_student_global[className]
            dict_grade_list["class_nums_student"][grade] = class_nums_student

        for grade in grade_set:
            dict_grade_list["grade"][str(grade)] = sum(
                dict_grade_list["class_nums_student"][str(grade)].values()
            )

        for i in major_list:
            dict_grade_list["major"][str(i)] = dict()
        for i in grade_set:
            dict_grade_list["major"]["ALL"][str(i)] = dict_grade_list["grade"][str(i)]
        for i in major_list:
            if str(i) != "ALL":
                for j in grade_set:
                    dict_grade_list["major"][str(i)][str(j)] = 0
                    for className, value in dict_grade_list["class_nums_student"][
                        str(j)
                    ].items():
                        if className.find(str(i)) != -1:
                            dict_grade_list["major"][str(i)][str(j)] += value
        if not sqlState:
            state_insert = models.ResultReadState(key=key)
            db.add(state_insert)
            db.commit()
            db.refresh(state_insert)
        await redis_store.setex(
            key,
            config.FAILED_STUID_INFO_REDIS_CACHE_EXPIRES,
            json.dumps(dict_grade_list, ensure_ascii=False),
        )
    else:
        dict_grade_list = await redis_store.get(key)
        dict_grade_list = json.loads(dict_grade_list)
    print("dict_grade_list:{}".format(dict_grade_list))
    return dict_grade_list


async def get_grade(className):
    """
    获取年级信息
    :param className:
    :return:
    """
    return str(className[-4:-2])


async def get_each_term_courseName(db: Session, term):
    """
    获取指定学期的课程名称
    :param term: 1 代表第一学期
    :param db:
    :return: ['软件工程', '足球（二）', '足球（一）', '计算机通信与网络实验']
    """
    term = str(term) + "_"
    try:
        term_courseName = (
            await db.query(models.Courses).filter(models.Courses.term.like(term)).all()
        )
        score_courseName = (
            await db.query(models.Scores).filter(models.Scores.term.like(term)).all()
        )
    except Exception as E:
        logging.error("访问数据库发生错误：" + str(E))
        return -1
    # 找到上课人数少于 10人的
    student_in_course = {}
    for sc in score_courseName:
        if sc.courseName not in student_in_course:
            student_in_course[sc.courseName] = 1
        else:
            student_in_course[sc.courseName] += 1

    term_courseName_list = []
    for className in term_courseName:
        # if className.courseName not in NOT_SHOW_COURSENAME and className.courseName not in lower_num_course:
        if (
            className.courseName not in config.NOT_SHOW_COURSE_NAME
            and className.courseName
        ):
            term_courseName_list.append(className.courseName)

    term_courseName_list = set(term_courseName_list)

    return term_courseName_list
