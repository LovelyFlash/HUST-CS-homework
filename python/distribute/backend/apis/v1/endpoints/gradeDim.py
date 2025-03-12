import json
import logging
import typing as t

from fastapi import APIRouter, Request, Response, Depends, status, HTTPException
from sqlalchemy.orm import Session
from sqlalchemy import distinct, and_, func, create_engine
from aioredis import Redis

from starlette.responses import FileResponse
from database.session import get_db
import models
import schemas
from schemas.basic import Response200, Response400
from database.redis import course_cache
from core.config import config
from .commonCourse import get_each_grade_class_number, get_lower_course_name
from utils.common import create_form, to_pinyin

gradeDim_router = APIRouter()


@gradeDim_router.post("/scores/grade")
async def get_grade_by_term(queryItem: schemas.BaseQuery, db: Session = Depends(get_db), redis_store: Redis = Depends(course_cache)):
    """
    年级维度
    返回四个年级第 term 学期的所有课程信息
    :param term:
    :return:
    """
    term = int(queryItem.term)
    key = "grade_by_term_" + str(term)
    sqlState = db.query(models.ResultReadState).filter(models.ResultReadState.key==key).first()
    redisState = await redis_store.exists(key)
    if (not sqlState) or redisState == 0:
        if not sqlState:  # 更新数据
            # 1. 得到一些基本信息（年级人数，班级人数）
            each_grade_class_number = await get_each_grade_class_number(db, redis_store)
            # 2. 四个grade
            gradeList = each_grade_class_number["grade"].keys()
            # 获取人数较少的（可能是转专业的课程）
            low_courseName_list_grade = await get_lower_course_name(term, gradeList, db, redis_store)

            ret = []
            for grade in gradeList:
                courseInfo = db.query(models.Scores).filter(and_(models.Scores.grade == grade, models.Scores.term == term)).with_entities(
                    models.Scores.courseName, models.Scores.failed).all()
                # 将数据组织成
                """
                {
                    "courseName":[],
                    "failed_nums":[],
                    "failed_rates":[]
                }
                """
                tmpDict = {
                    "term":str(term),
                    "grade": str(grade),
                    "courseName": [],
                    "failed_nums": [],
                    "failed_rates": []
                }
                for row in courseInfo:
                    if row[0] not in low_courseName_list_grade[str(grade)] and row[1] == 1:
                        tmp_courseName = row[0]
                        tmp_courseName = tmp_courseName.replace('（', '︵')
                        tmp_courseName = tmp_courseName.replace('）', '︶')
                        tmp_courseName = tmp_courseName.replace(')', '︶')
                        tmp_courseName = tmp_courseName.replace('(', '︵')
                        if tmp_courseName not in tmpDict["courseName"]:
                            tmpDict["courseName"].append(tmp_courseName)
                            tmpDict["failed_nums"].append(1)
                        else:
                            tmpDict["failed_nums"][tmpDict["courseName"].index(
                                tmp_courseName)] += 1
                gradeNum = each_grade_class_number["grade"][str(grade)]
                for i in range(len(tmpDict["courseName"])):
                    tmpDict["failed_rates"].append("{:.2f}".format(
                        float("{:.4f}".format(tmpDict["failed_nums"][i] / gradeNum))*100))

                # 重新排序，具体思路：将数据重组为元组，然后排序，排序之后再打散
                tuple_tmpDict = []
                for i in range(len(tmpDict["courseName"])):
                    tuple_tmpDict.append(
                        (tmpDict["courseName"][i], tmpDict["failed_nums"][i], tmpDict["failed_rates"][i]))
                tuple_tmpDict = sorted(
                    tuple_tmpDict, key=lambda t: t[1], reverse=True)
                tmpDict = {
                    "term":str(term),
                    "grade": str(grade),
                    "courseName": [],
                    "failed_nums": [],
                    "failed_rates": []
                }
                for i in range(len(tuple_tmpDict)):
                    tmpDict["courseName"].append(tuple_tmpDict[i][0])
                    tmpDict["failed_nums"].append(tuple_tmpDict[i][1])
                    tmpDict["failed_rates"].append(tuple_tmpDict[i][2])
                if tmpDict["courseName"] != []:
                    ret.append(tmpDict)
            if len(ret) != 0:
                # 将计算好的数据写入数据库
                for gradeItem in ret:
                    grade = gradeItem["grade"]
                    gradeDimQuery = db.query(models.GradeByTerm).filter(and_(
                        models.GradeByTerm.term == str(term), models.GradeByTerm.grade == str(grade))).first()
                    if gradeDimQuery:
                        db.query(models.GradeByTerm).filter(
                            and_(
                                models.GradeByTerm.term == str(term), 
                                models.GradeByTerm.grade == str(grade)
                            )
                        ).delete()
                        db.commit()
                    print("将 年级维度的 计算结果保存到数据库...")
                    gradeDimInsert = models.GradeByTerm(term=str(term), grade=str(grade),
                                                        courseName=str(
                                                            gradeItem['courseName']),
                                                        failed_nums=str(
                                                            gradeItem['failed_nums']),
                                                        failed_rates=str(gradeItem['failed_rates']))
                    db.add(gradeDimInsert)
                    db.commit()
                    db.refresh(gradeDimInsert)
                
            else:
                return Response400(msg="没有查询到相关数据，请检查查询关键字 or 数据库数据是否为空")
            state_insert = models.ResultReadState(key=key)
            db.add(state_insert)
            db.commit()
            db.refresh(state_insert)
        else:
            # 直接读取计算好的数据
            retDb = db.query(models.GradeByTerm).filter(models.GradeByTerm.term == str(term)).all()
            ret = []
            # print("="*50)
            for dbItem in retDb:
                ret.append(
                    {
                        "term": dbItem.term,
                        "grade": dbItem.grade,
                        "courseName": eval(dbItem.courseName) if dbItem.courseName != '' else [],
                        "failed_nums": eval(dbItem.failed_nums) if dbItem.courseName != '' else [],
                        "failed_rates": eval(dbItem.failed_rates)  if dbItem.courseName != '' else [],
                    }
                )
        if(len(ret) != 0):
            # 将数据写入缓存
            await redis_store.setex(key, config.FAILED_STUID_INFO_REDIS_CACHE_EXPIRES, json.dumps(ret, ensure_ascii=False))
        else:
            return Response400(data="中间结果数据库中暂时无数据，请在文件上传页面切换读取数据方式为从原始数据读取之后再请求")
    else:
        ret = json.loads(await redis_store.get(key))

    return Response200(data=ret)

@gradeDim_router.post("/grade/download")
async def download_grade_file_by_term(queryItem: schemas.gradeFile, db: Session=Depends(get_db)):
    grade = str(queryItem.grade)
    term = str(queryItem.term)
    fileName = grade + "_grade_" + term + "_term.xlsx"
    FORM_HEADER = ["学号", "姓名", "班级", "不及格科目数", "不及格科目名"]
    FORM_DATA = []
    stuIDList = db.query(models.Scores).filter(models.Scores.grade==grade, models.Scores.term==term, models.Scores.score < 60).with_entities(models.Scores.stuID).order_by(models.Scores.stuID).distinct().all()
    print(stuIDList)
    if len(stuIDList) == 0:
        return HTTPException()
    for row in stuIDList:
        stuID = row[0]
        student: models.Students = db.query(models.Students).filter(models.Students.stuID==stuID).first()
        stuName = student.stuName
        stuClass = student.stuClass
        scoreList: list[models.Scores] = db.query(models.Scores).filter(models.Scores.stuID==stuID, models.Scores.score < 60).distinct().all()
        failNumber = len(scoreList)
        failList = []
        for score in scoreList:
            failList.append(score.courseName)
        failList.sort(key=lambda x:to_pinyin(x))
        failName = ""
        for name in failList:
            failName += name + ","
        failName = failName.rstrip(",")
        FORM_DATA.append([stuID, stuName, stuClass, failNumber, failName])
    create_form(config.SAVE_FAILED_STUDENT_BY_TERM_FILE_DIR + fileName, FORM_DATA, FORM_HEADER)
    return FileResponse(path=config.SAVE_FAILED_STUDENT_BY_TERM_FILE_DIR + fileName, filename=fileName)