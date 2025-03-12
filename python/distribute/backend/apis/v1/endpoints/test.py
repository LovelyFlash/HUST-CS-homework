# from fastapi import APIRouter,Depends
# from sqlalchemy import within_group
# from sqlalchemy.orm import Session

# # import models
# from schemas import Response200
# from database.session import get_db_async,async_engine

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

from apis.v1.endpoints.commonCourse import get_each_grade_class_number, get_lower_course_name, get_major_list

from apis.v1.endpoints.studentInfo import getStudentInfoByGrade

from database.session import get_db
import models
import schemas
from schemas.basic import Response200, Response400
from database.redis import course_cache
from core.config import config
from utils.common import to_pinyin,create_form


test_api = APIRouter()

@test_api.get('/test/major')
async def test_major( db: Session = Depends(get_db), redis_store: Redis = Depends(course_cache)):
    ret = await get_each_grade_class_number(db, await course_cache())
    return Response200(data=ret)

@test_api.get("/test/studentInfo/<grade>")
async def test_student(grade: int):
    result = getStudentInfoByGrade(grade)
    return Response200(data=result)

async def assignCourseType(db: Session=Depends(get_db), redis_store: Redis=Depends(course_cache)):
    grade_class_info = await get_each_grade_class_number(db, redis_store)
    gradeList = grade_class_info["grade"].keys()
    courseFileList = os.listdir(config.SAVE_COURSE_FILE_DIR)
    for grade in gradeList:
        courseFileName = str(grade) + '_grade_course.xlsx'
        courseList = []
        courseDict = {}
        if courseFileName in courseFileList:
            result = pd.read_excel(config.SAVE_COURSE_FILE_DIR + courseFileName)
            for i in range(len(result)):
                courseList.append([result.iloc[i,0], result.iloc[i,1]])
                courseDict[str(result.iloc[i, 0])] = result.iloc[i,1]
        res: list[models.Courses] = db.query(models.Courses).filter(models.Courses.grade==grade).all()
        res.sort(key=lambda x: to_pinyin(x.courseName))
        for course in res:
            if course.courseName in courseDict.keys():
                db.query(models.Courses).filter(models.Courses.courseName==course.courseName).update({"type": courseDict[course.courseName]})
                db.commit()
            else:
                courseDict[course.courseName] = course.type
                courseList.append([course.courseName, course.type])
        FORM_HEADER = ["课程名", "类型"]
        FORM_DATA = []
        courseList.sort(key=lambda x: to_pinyin(x[0]))
        for item in courseList:
            FORM_DATA.append(item)
        create_form(config.SAVE_COURSE_FILE_DIR + courseFileName, FORM_HEADER)

class TestClass:
    
    config = 1
    
if __name__ == '__main__':
    
    a = TestClass()
    print(a.config)
    a.config = 2
    print(a.config)
    
