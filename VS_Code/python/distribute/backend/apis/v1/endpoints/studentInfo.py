import json
import logging
from os import stat
from pyexpat import model
import re
from statistics import mode

from fastapi import APIRouter, Request, Response, Depends, status, HTTPException
from sqlalchemy.orm import Session
from sqlalchemy import and_, or_
from aioredis import Redis


from database.session import get_db
import models
import schemas
from schemas.basic import Response200, Response400
from starlette.responses import FileResponse
from database.redis import stuInfo_cache, course_cache
from .commonCourse import get_each_grade_class_number
from core.config import config
from database.curd_ec import (
    ec_getCurrentYear,
    ec_get_by_year,
    ec_getYearList,
    ec_get_by_grade,
    ec_gradeToYear,
    ec_getGradeList,
    ec_get_info_by_grade_year,
)
from utils.common import to_pinyin, create_form

stuInfo_router = APIRouter()


@stuInfo_router.get("/studentInfo/number")
async def getEachGradeNumber(
    db: Session = Depends(get_db), redis_store: Redis = Depends(course_cache)
):
    """
    numberDictList = [
        {
            "grade": 20,
            "total": 480,
            "major":[
                {
                    "key": CS,
                    "value": 420,
                    "rate": 0.85
                }
                ...
            ]
        },
        ...
    ]
    """
    key = "eachGradeNumber"
    sqlState = (
        db.query(models.ResultReadState)
        .filter(models.ResultReadState.key == key)
        .first()
    )
    redisState = await redis_store.exists(key)
    if (not sqlState) or redisState == 0:
        numberDictList = []
        grade_class_info = await get_each_grade_class_number(db, redis_store)
        for grade in grade_class_info["grade"].keys():
            gradeDict = {}
            gradeDict["grade"] = str(grade)
            gradeDict["total"] = grade_class_info["grade"][str(grade)]
            gradeDict["major"] = []
            for major in grade_class_info["major"].keys():
                if (
                    major != "ALL"
                    and grade_class_info["major"][str(major)][str(grade)] != 0
                ):
                    gradeDict["major"].append(
                        {
                            "key": major,
                            "value": grade_class_info["major"][str(major)][str(grade)],
                            "rate": round(
                                grade_class_info["major"][str(major)][str(grade)]
                                / gradeDict["total"]
                                * 100.0,
                                2,
                            ),
                        }
                    )
            numberDictList.append(gradeDict)
        if not sqlState:
            state_insert = models.ResultReadState(key=key)
            db.add(state_insert)
            db.commit()
            db.refresh(state_insert)
        await redis_store.setex(
            key,
            config.CLASS_INFO_REDIS_CACHE_EXPIRES,
            json.dumps(numberDictList, ensure_ascii=False),
        )
    else:
        numberDictList = json.loads(await redis_store.get(key))
    return Response200(data=numberDictList)


@stuInfo_router.post("/studentInfo/grade")
async def getStudentInfoByGrade(
    queryItem: schemas.GradeQuery,
    redis_store: Redis = Depends(stuInfo_cache),
    db: Session = Depends(get_db),
):
    """
    请求某个年级的所有不及格学生的信息
    :param grade: 18 19 20 21
    :return:
    """
    grade = int(queryItem.grade)
    key = "studentInfo_" + str(grade)
    sqlState = (
        db.query(models.ResultReadState)
        .filter(models.ResultReadState.key == key)
        .first()
    )
    redisState = await redis_store.exists(key)
    if (not sqlState) or redisState == 0:
        if not sqlState:  # 更新数据
            course_credit_dict = await get_course_credit(db, grade)  # 课程:学分,类型
            allFailedStudentInfos = []
            # 从score 中获取所有成绩有不及格情况的同学
            stuID_list = await get_failedStuID_by_grade(db, grade)

            for stuID in stuID_list:
                dict_stuInfo = await get_stuInfo_by_grade(
                    db, stuID, course_credit_dict, grade
                )
                if dict_stuInfo["failedSubjectNums"] != 0:
                    allFailedStudentInfos.append(dict_stuInfo)
            print(allFailedStudentInfos)

            if len(allFailedStudentInfos) != 0:
                # 将计算好的数据写入到数据库
                for studentInfoItem in allFailedStudentInfos:
                    studentInfoQuery = db.query(models.StudentInfo).filter(models.StudentInfo.stuID == studentInfoItem["stuID"]).first()
                    if studentInfoQuery:
                        db.query(models.StudentInfo).filter(models.StudentInfo.stuID == studentInfoItem["stuID"]).delete()
                        db.commit()
                    sqlInsert = models.StudentInfo(
                        stuID = studentInfoItem["stuID"],
                        grade = studentInfoItem["grade"],
                        stuName = studentInfoItem["stuName"],
                        stuClass = studentInfoItem["stuClass"],
                        totalWeightedScore = studentInfoItem["totalWeightedScore"],
                        failedSubjectNames = studentInfoItem["failedSubjectNames"],
                        failedSubjectTermNames = str(studentInfoItem["failedSubjectTermNames"]),
                        failedSubjectNums = studentInfoItem["failedSubjectNums"],
                        sumFailedCreditALL = studentInfoItem["sumFailedCreditALL"],
                        totalCreditALL = studentInfoItem["totalCreditALL"],
                        sumFailedCreditUnclassified = studentInfoItem["sumFailedCreditUnclassified"],
                        totalCreditUnclassified = studentInfoItem["totalCreditUnclassified"],
                        sumFailedCreditPublicCompulsory = studentInfoItem["sumFailedCreditPublicCompulsory"],
                        totalCreditPublicCompulsory = studentInfoItem["totalCreditPublicCompulsory"],
                        sumFailedCreditProfessionalCompulsory = studentInfoItem["sumFailedCreditProfessionalCompulsory"],
                        totalCreditProfessionalCompulsory = studentInfoItem["totalCreditProfessionalCompulsory"],
                        sumFailedCreditProfessionalElective = studentInfoItem["sumFailedCreditProfessionalElective"],
                        totalCreditProfessionalElective = studentInfoItem["totalCreditProfessionalElective"],
                        sumFailedCreditPublicElective = studentInfoItem["sumFailedCreditPublicElective"],
                        totalCreditPublicElective = studentInfoItem["totalCreditPublicElective"],
                        failedSubjectNumsTerm = str(studentInfoItem["failedSubjectNumsTerm"]),
                        totalWeightedScoreTerm = str(studentInfoItem["totalWeightedScoreTerm"]),
                        totalFailedCreditTerm = str(studentInfoItem["totalFailedCreditTerm"]),
                        totalCreditExcludePublicElective = str(studentInfoItem["totalCreditExcludePublicElective"]),
                        totalCreditIncludePublicElective = str(studentInfoItem["totalCreditIncludePublicElective"]),
                        requiredCreditExcludePublicElective = str(studentInfoItem["requiredCreditExcludePublicElective"]),
                        requiredCreditIncludePublicElective = str(studentInfoItem["requiredCreditIncludePublicElective"]),
                        excludePublicElectiveType = str(studentInfoItem["excludePublicElectiveType"]),
                        includePublicElectiveType = str(studentInfoItem["includePublicElectiveType"]),
                    )
                    db.add(sqlInsert)
                    db.commit()
                    db.refresh(sqlInsert)
                state_insert = models.ResultReadState(key=key)
                db.add(state_insert)
                db.commit()
                db.refresh(state_insert)
            else:
                return Response400(
                    msg="没有查询到相关数据，请检查查询关键字 or 数据库数据是否为空"
                )

        else:
            # 直接读取已经计算好的数据
            retDb: list[models.StudentInfo] = (
                db.query(models.StudentInfo)
                .filter(models.StudentInfo.grade == str(grade))
                .all()
            )
            allFailedStudentInfos = []
            for dbItem in retDb:
                allFailedStudentInfos.append({
                        "stuID" : dbItem.stuID,
                        "grade" : dbItem.grade,
                        "stuName" : dbItem.stuName,
                        "stuClass" : dbItem.stuClass,
                        "totalWeightedScore" : dbItem.totalWeightedScore,
                        "failedSubjectNames" : dbItem.failedSubjectNames,
                        "failedSubjectTermNames" : eval(dbItem.failedSubjectTermNames),
                        "failedSubjectNums" : dbItem.failedSubjectNums,
                        "sumFailedCreditALL" : dbItem.sumFailedCreditALL,
                        "totalCreditALL" : dbItem.totalCreditALL,
                        "sumFailedCreditUnclassified" : dbItem.sumFailedCreditUnclassified,
                        "totalCreditUnclassified" : dbItem.totalCreditUnclassified,
                        "sumFailedCreditPublicCompulsory" : dbItem.sumFailedCreditPublicCompulsory,
                        "totalCreditPublicCompulsory" : dbItem.totalCreditPublicCompulsory,
                        "sumFailedCreditProfessionalCompulsory" : dbItem.sumFailedCreditProfessionalCompulsory,
                        "totalCreditProfessionalCompulsory" : dbItem.totalCreditProfessionalCompulsory,
                        "sumFailedCreditProfessionalElective" : dbItem.sumFailedCreditProfessionalElective,
                        "totalCreditProfessionalElective" : dbItem.totalCreditProfessionalElective,
                        "sumFailedCreditPublicElective" : dbItem.sumFailedCreditPublicElective,
                        "totalCreditPublicElective" : dbItem.totalCreditPublicElective,
                        "failedSubjectNumsTerm" : eval(dbItem.failedSubjectNumsTerm),
                        "totalWeightedScoreTerm" : eval(dbItem.totalWeightedScoreTerm),
                        "totalFailedCreditTerm" : eval(dbItem.totalFailedCreditTerm),
                        "totalCreditExcludePublicElective" : dbItem.totalCreditExcludePublicElective,
                        "totalCreditIncludePublicElective" : dbItem.totalCreditIncludePublicElective,
                        "requiredCreditExcludePublicElective" : dbItem.requiredCreditExcludePublicElective,
                        "requiredCreditIncludePublicElective" : dbItem.requiredCreditIncludePublicElective,
                        "excludePublicElectiveType" : dbItem.excludePublicElectiveType,
                        "includePublicElectiveType" : dbItem.includePublicElectiveType,
                    })
        # 将数据写入 redis
        if len(allFailedStudentInfos) != 0:
            try:

                resp_json = json.dumps(allFailedStudentInfos, ensure_ascii=False)
                await redis_store.setex(
                    key,
                    config.FAILED_STUID_INFO_REDIS_CACHE_EXPIRES,
                    resp_json,
                )
            except Exception as E:
                logging.error("写入 redis 异常 %s" % E)

                return Response400(msg="写入 redis 异常 %s" % str(E))
        else:
            return Response400(
                data="中间结果数据库中暂时无数据，请在文件上传页面切换读取数据方式为从原始数据读取之后再请求"
            )
        return Response200(data=allFailedStudentInfos)
    else:
        resp_data = await redis_store.get(key)
        if isinstance(resp_data, str):
            resp_data = json.loads(resp_data)
        return Response200(data=resp_data)

async def get_course_credit(db: Session, grade):
    """

    :return:
    {
        "courseName1":credit1,
        "courseName2":credit2,
    }
    """
    # 后序优化：将这些数据存在 redis中
    dict_course_credit = {}
    courseList: list[models.Courses] = db.query(models.Courses).filter(models.Courses.grade==grade).all()
    for course in courseList:
        dict_course_credit[course.courseName] = {"credit": course.credit, "type": course.type}
    return dict_course_credit


async def get_failedStuID_by_grade(db: Session, grade):
    """
    获取考试有不及格情况同学的学号信息
    :return:
    {
        {
            "stuIndex": 1,
            "stuID": "U201514480"
        },
        {
            "stuIndex": 1,
            "stuID": "U201514480"
        }
    }
    """
    #  查询学号 成绩 < 60, 对查询结果降序排序
    results = (
        db.query(models.Scores)
        .with_entities(models.Scores.stuID)
        .distinct()
        .filter(models.Scores.score < 60, models.Scores.grade==grade)
        .order_by(models.Scores.stuID.asc())
    )
    stuID_list = []
    for res in results:
        stuID_list.append(res[0])
    return stuID_list


async def get_stuInfo_by_grade(db: Session, stuID, course_credit_dic, grade):
    """

    :param stuID:
    :param course_credit_dic:
    :param grade:
    :return:
    """
    """
        根据学号，找到这个学生需要的所有信息
        :param stuID:
        :return:
        {
            "stuID": "stuID",
            "stuName": "stuName",
            "stuClass": "CS1707",
            ...
        }
        """
    failedStudentDict = {}
    failedStudentDict["stuID"] = stuID
    failedStudentDict["grade"] = grade
    res: models.Students = db.query(models.Students).filter(models.Students.stuID==stuID).first()
    failedStudentDict["stuName"] = res.stuName
    if "BD" in res.stuClass:
        failedStudentDict["stuClass"] = "大数据" + res.stuClass[-4:]
    elif "BSB" in res.stuClass:
        failedStudentDict["stuClass"] = "本硕博" + res.stuClass[-4:]
    elif "ZY" in res.stuClass:
        failedStudentDict["stuClass"] = "卓越(创新)" + res.stuClass[-4:]
    elif "IOT" in res.stuClass:
        failedStudentDict["stuClass"] = "物联网" + res.stuClass[-4:]
    elif "XJ" in res.stuClass:
        failedStudentDict["stuClass"] = "校交" + res.stuClass[-4:]
    elif "IST" in res.stuClass:
        failedStudentDict["stuClass"] = "智能" + res.stuClass[-4:]
    elif "TL" in res.stuClass:
        failedStudentDict["stuClass"] = "图灵" + res.stuClass[-4:]
    elif "CS" in res.stuClass:
        failedStudentDict["stuClass"] = "计算机" + res.stuClass[-4:]
    failedStudentDict["totalWeightedScore"] = 0.0 # 只计算type=1,2,3
    failedStudentDict["failedSubjectNames"] = ""
    failedStudentDict["failedSubjectTermNames"] = []
    failedStudentDict["failedSubjectNums"] = 0
    
    # 全部
    failedStudentDict["sumFailedCreditALL"] = 0.0
    failedStudentDict["totalCreditALL"] = 0.0
    # type=0 未分类
    failedStudentDict["sumFailedCreditUnclassified"] = 0.0
    failedStudentDict["totalCreditUnclassified"] = 0.0
    # type=1 公共必修
    failedStudentDict["sumFailedCreditPublicCompulsory"] = 0.0
    failedStudentDict["totalCreditPublicCompulsory"] = 0.0
    # type=2 专业必修
    failedStudentDict["sumFailedCreditProfessionalCompulsory"] = 0.0
    failedStudentDict["totalCreditProfessionalCompulsory"] = 0.0
    # type=3 专业选修
    failedStudentDict["sumFailedCreditProfessionalElective"] = 0.0
    failedStudentDict["totalCreditProfessionalElective"] = 0.0
    # type=4 公共选修
    failedStudentDict["sumFailedCreditPublicElective"] = 0.0
    failedStudentDict["totalCreditPublicElective"] = 0.0
    
    # 每学年挂科数量
    failedStudentDict["failedSubjectNumsTerm"] = []  
    # 每学加权平均分
    failedStudentDict["totalWeightedScoreTerm"] = []
    failedStudentDict["totalFailedCreditTerm"] = []
    
    failedCourseList = []
    totalWeightCredit = 0.0
    totalWeightCreditTerm = 0.0
    
    failedStudentDict["totalCreditExcludePublicElective"] = 0.0
    failedStudentDict["totalCreditIncludePublicElective"] = 0.0
    failedStudentDict["requiredCreditExcludePublicElective"] = 0.0
    failedStudentDict["requiredCreditIncludePublicElective"] = 0.0
    
    failedStudentDict["excludePublicElectiveType"] = 0
    failedStudentDict["includePublicElectiveType"] = 0
    
    termList = ["11", "12", "21", "22", "31", "32", "41", "42"]
    for term in termList:
        failedCourseTermList = []
        scoreList: list[models.Scores] = db.query(models.Scores).filter(models.Scores.stuID==stuID, models.Scores.term==term).all()
        if not scoreList:
            continue
        failedStudentDict["failedSubjectNumsTerm"].append(0)
        failedStudentDict["totalWeightedScoreTerm"].append(0.0)
        failedStudentDict["totalFailedCreditTerm"].append(0.0)
        failedStudentDict["failedSubjectTermNames"].append("")
        totalWeightCreditTerm = 0.0
        for score in scoreList:
            courseInfo = course_credit_dic[score.courseName]
            if score.score < 60:
                failedStudentDict["sumFailedCreditALL"] += courseInfo["credit"]
                if courseInfo["type"] in [1, 2]:
                    failedCourseList.append(score.courseName)
                    failedCourseTermList.append(score.courseName)
                    failedStudentDict["failedSubjectNums"] += 1
                    failedStudentDict["failedSubjectNumsTerm"][-1] += 1
                    failedStudentDict["totalFailedCreditTerm"][-1] += courseInfo["credit"]
                if courseInfo["type"] == 0:
                    failedStudentDict["sumFailedCreditUnclassified"] += courseInfo["credit"]
                elif courseInfo["type"] == 1:
                    failedStudentDict["sumFailedCreditPublicCompulsory"] += courseInfo["credit"]
                elif courseInfo["type"] == 2:
                    failedStudentDict["sumFailedCreditProfessionalCompulsory"] += courseInfo["credit"]
                elif courseInfo["type"] == 3:
                    failedStudentDict["sumFailedCreditProfessionalElective"] += courseInfo["credit"]
                elif courseInfo["type"] == 4:
                    failedStudentDict["sumFailedCreditPublicElective"] += courseInfo["credit"]
            else:
                failedStudentDict["totalCreditALL"] += courseInfo["credit"]
                if courseInfo["type"] in [1, 2, 3]:
                    failedStudentDict["totalCreditExcludePublicElective"] += courseInfo["credit"]
                if courseInfo["type"] in [1, 2, 3, 4]:
                    failedStudentDict["totalCreditIncludePublicElective"] += courseInfo["credit"]
                if courseInfo["type"] == 0:
                    failedStudentDict["totalCreditUnclassified"] += courseInfo["credit"]
                elif courseInfo["type"] == 1:
                    failedStudentDict["totalCreditPublicCompulsory"] += courseInfo["credit"]
                elif courseInfo["type"] == 2:
                    failedStudentDict["totalCreditProfessionalCompulsory"] += courseInfo["credit"]
                elif courseInfo["type"] == 3:
                    failedStudentDict["totalCreditProfessionalElective"] += courseInfo["credit"]
                elif courseInfo["type"] == 4:
                    failedStudentDict["totalCreditPublicElective"] += courseInfo["credit"]

            if courseInfo["type"] in [1, 2, 3]:
                    failedStudentDict["totalWeightedScore"] += score.score * courseInfo["credit"]
                    failedStudentDict["totalWeightedScoreTerm"][-1] += score.score * courseInfo["credit"]
                    totalWeightCredit += courseInfo["credit"]
                    totalWeightCreditTerm += courseInfo["credit"]
        if totalWeightCreditTerm != 0.0:
            failedStudentDict["totalWeightedScoreTerm"][-1] = round(failedStudentDict["totalWeightedScoreTerm"][-1] / totalWeightCreditTerm, 2)
        failedSubjectTermNames = ""
        failedCourseTermList.sort(key=lambda x:to_pinyin(x))
        for course in failedCourseTermList:
            failedSubjectTermNames += str(course) + ","
        failedStudentDict["failedSubjectTermNames"][-1] = failedSubjectTermNames.rstrip(',')
    
    if totalWeightCredit != 0.0:
        failedStudentDict["totalWeightedScore"] = round(failedStudentDict["totalWeightedScore"] / totalWeightCredit, 2)
    failedCourseList.sort(key=lambda x:to_pinyin(x))
    for course in failedCourseList:
        failedStudentDict["failedSubjectNames"] += str(course) + ","
    failedStudentDict["failedSubjectNames"] = failedStudentDict["failedSubjectNames"].rstrip(',')
    major = re.search(r"[A-Z]+", res.stuClass).group()
    studentInfoConfig: models.StudentInfoConfig = db.query(models.StudentInfoConfig).filter(models.StudentInfoConfig.grade==grade, models.StudentInfoConfig.major==major).first()
    if not studentInfoConfig:
        failedStudentDict["requiredCreditExcludePublicElective"] = 0.0
        failedStudentDict["requiredCreditIncludePublicElective"] = 0.0
        failedStudentDict["excludePublicElectiveType"] = 0
        failedStudentDict["includePublicElectiveType"] = 0
    else:
        failedStudentDict["requiredCreditExcludePublicElective"] = studentInfoConfig.requiredCreditExcludePublicElective
        failedStudentDict["requiredCreditIncludePublicElective"] = studentInfoConfig.requiredCreditIncludePublicElective
        
        if failedStudentDict["totalCreditExcludePublicElective"] / failedStudentDict["requiredCreditExcludePublicElective"] < studentInfoConfig.redRate:
            failedStudentDict["excludePublicElectiveType"] = 3
        elif failedStudentDict["totalCreditExcludePublicElective"] / failedStudentDict["requiredCreditExcludePublicElective"] < studentInfoConfig.yellowRate:
            failedStudentDict["excludePublicElectiveType"] = 2
        else:
            failedStudentDict["excludePublicElectiveType"] = 1
        
        if failedStudentDict["totalCreditIncludePublicElective"] / failedStudentDict["requiredCreditIncludePublicElective"] < studentInfoConfig.redRate:
            failedStudentDict["includePublicElectiveType"] = 3
        elif failedStudentDict["totalCreditIncludePublicElective"] / failedStudentDict["requiredCreditIncludePublicElective"] < studentInfoConfig.yellowRate:
            failedStudentDict["includePublicElectiveType"] = 2
        else:
            failedStudentDict["includePublicElectiveType"] = 1

    # # 获取其个人评价
    # stuAnalysisInfo = (
    #     db.query(models.StuAnalysis)
    #     .filter(models.StuAnalysis.stuID == stuID, models.StuAnalysis.stuType == 3)
    #     .all()
    # )

    # selfContent = {}
    # if stuAnalysisInfo:
    #     for i in range(len(stuAnalysisInfo)):
    #         selfContent[
    #             "term" + str(stuAnalysisInfo[i].term // 10) + "_selfcontent"
    #         ] = stuAnalysisInfo[i].content1
    # failedStudentDict["selfContent"] = selfContent
    
    return failedStudentDict

@stuInfo_router.post("/studentInfo/setConfig")
async def set_grade_config(queryItem: schemas.StudentInfoConfig, db:Session = Depends(get_db)):
    grade = str(queryItem.grade)
    major = str(queryItem.major)
    redRate = float(queryItem.redRate)
    yellowRate = float(queryItem.yellowRate)
    requiredCreditExcludePublicElective = float(queryItem.requiredCreditExcludePublicElective)
    requiredCreditIncludePublicElective = float(queryItem.requiredCreditIncludePublicElective)
    key = "studentInfo_" + str(grade)
    db.query(models.StudentInfoConfig).filter(models.StudentInfoConfig.grade==grade, models.StudentInfoConfig.major==major).delete()
    db.query(models.ResultReadState).filter(models.ResultReadState.key==key).delete()
    db.commit()
    sql_insert = models.StudentInfoConfig(
        grade = grade,
        major = major,
        redRate = redRate,
        yellowRate = yellowRate,
        requiredCreditExcludePublicElective = requiredCreditExcludePublicElective,
        requiredCreditIncludePublicElective = requiredCreditIncludePublicElective,
    )
    db.add(sql_insert)
    db.commit()
    db.refresh(sql_insert)
    return Response200()


@stuInfo_router.post("/studentInfo/download")
async def download_student_info_file(queryItem: schemas.StudentInfoDownload, db: Session=Depends(get_db)):
    grade = str(queryItem.grade)
    red = int(queryItem.red)
    yellow = int(queryItem.yellow)
    white = int(queryItem.white)
    type = int(queryItem.type)
    fileName = grade + "_grade" + ("_red" if red == True else "") + ("_yellow" if yellow == True else "") + ("_white" if white == True else "") + ("_exclude_publicElective.xlsx" if type == True else "_include_publicElective.xlsx") 
    redItem = []
    yellowItem = []
    whiteItem = []
    unclassifiedItem = []
    studentInfoList: list[models.StudentInfo] = db.query(models.StudentInfo).filter(models.StudentInfo.grade==grade).all()
    studentInfoList.sort(key=lambda x:x.failedSubjectNums * 1000 + x.sumFailedCreditALL, reverse=True)
    for i in range(len(studentInfoList)):
        studentInfo = studentInfoList[i]
        studentInfoItem = [
            i + 1,
            studentInfo.stuID, 
            studentInfo.stuName, 
            studentInfo.stuClass, 
            studentInfo.totalWeightedScore,
            studentInfo.totalCreditExcludePublicElective,
            studentInfo.totalCreditPublicCompulsory + studentInfo.totalCreditProfessionalCompulsory,
            studentInfo.totalCreditProfessionalElective,
            studentInfo.failedSubjectNums, 
            studentInfo.failedSubjectNames,
            ]
        if type == True:
            if studentInfo.excludePublicElectiveType == 3:
                redItem.append(studentInfoItem)
            elif studentInfo.excludePublicElectiveType == 2:
                yellowItem.append(studentInfoItem)
            elif studentInfo.excludePublicElectiveType == 1:
                whiteItem.append(studentInfoItem)
            else:
                unclassifiedItem.append(studentInfoItem)
        else:
            if studentInfo.includePublicElectiveType == 3:
                redItem.append(studentInfoItem)
            elif studentInfo.includePublicElectiveType == 2:
                yellowItem.append(studentInfoItem)
            elif studentInfo.includePublicElectiveType == 1:
                whiteItem.append(studentInfoItem)
            else:
                unclassifiedItem.append(studentInfoItem)
    FORM_HEADER = [
        "序号",
        "学号",
        "姓名",
        "班级",
        "加权平均",
        "已修学分(总)",
        "已修学分(必修)",
        "已修学分(专选)",
        "累计不及格科目数(必修)",
        "不及格科目具体名称",
        ]
    FORM_DATA = []
    
    if red == True:
        FORM_DATA.append(["红牌:","","","","","","","","","",])
        for item in redItem:
            FORM_DATA.append(item)
    if yellow == True:
        FORM_DATA.append(["黄牌:","","","","","","","","","",])
        for item in yellowItem:
            FORM_DATA.append(item)
    if white == True:
        FORM_DATA.append(["普通:","","","","","","","","","",])
        for item in whiteItem:
            FORM_DATA.append(item)
    if len(unclassifiedItem) != 0:
        FORM_DATA.append(["信息缺失:","","","","","","","","","",])
        for item in unclassifiedItem:
            FORM_DATA.append(item)
    index = 1
    for item in FORM_DATA:
        if (item[0] == "红牌:" or item[0] == "黄牌:" or item[0] == "普通:" or item[0] == "信息缺失:"):
            continue
        item[0] = index
        index += 1
    create_form(config.SAVE_STUDENT_INFO_FILE_DIR + fileName, FORM_DATA, FORM_HEADER)
    return FileResponse(
    path=config.SAVE_STUDENT_INFO_FILE_DIR + fileName, filename=fileName
    )


@stuInfo_router.post("/studentInfo/downloadDetail")
async def download_student_info_detail_file(queryItem: schemas.GradeQuery, db: Session=Depends(get_db)):
    grade = str(queryItem.grade)
    studentInfoList: list[models.StudentInfo] = db.query(models.StudentInfo).filter(models.StudentInfo.grade==grade).all()
    studentInfoList.sort(key=lambda x:x.failedSubjectNums * 1000 + x.sumFailedCreditALL, reverse=True)
    fileName = grade + "_grade_studentInfo_detail.xlsx"
    FORM_HEADER = [
        "序号",
        "学号",
        "姓名",
        "班级",
        "加权平均",
        "已修学分(总)",
        "已修学分(必修)",
        "累计不及格科目数(必修)",
        "不及格科目具体名称",
        "第一学期不及格科目数",
        "第一学期不及格课程名称",
        "第二学期不及格科目数",
        "第二学期不及格课程名称",
        "第三学期不及格科目数",
        "第三学期不及格课程名称",
        "第四学期不及格科目数",
        "第四学期不及格课程名称",
        "第五学期不及格科目数",
        "第五学期不及格课程名称",
        "第六学期不及格科目数",
        "第六学期不及格课程名称",
        "第七学期不及格科目数",
        "第七学期不及格课程名称",
        "第八学期不及格科目数",
        "第八学期不及格课程名称",
        ]
    FORM_DATA = []
    for i in range(len(studentInfoList)):
        studentInfo = studentInfoList[i]
        failedSubjectTermNames = eval(studentInfo.failedSubjectTermNames)
        failedSubjectNumsTerm = eval(studentInfo.failedSubjectNumsTerm)
        
        FORM_DATA.append([
            i + 1,
            studentInfo.stuID,
            studentInfo.stuName,
            studentInfo.stuClass,
            studentInfo.totalWeightedScore,
            studentInfo.totalCreditExcludePublicElective,
            studentInfo.totalCreditPublicCompulsory + studentInfo.totalCreditProfessionalCompulsory,
            studentInfo.failedSubjectNums,
            studentInfo.failedSubjectNames,
            failedSubjectNumsTerm[0] if len(failedSubjectNumsTerm) > 0 else "",
            failedSubjectTermNames[0] if len(failedSubjectNumsTerm) > 0 else "",
            failedSubjectNumsTerm[1] if len(failedSubjectNumsTerm) > 1 else "",
            failedSubjectTermNames[1] if len(failedSubjectNumsTerm) > 1 else "",
            failedSubjectNumsTerm[2] if len(failedSubjectNumsTerm) > 2 else "",
            failedSubjectTermNames[2] if len(failedSubjectNumsTerm) > 2 else "",
            failedSubjectNumsTerm[3] if len(failedSubjectNumsTerm) > 3 else "",
            failedSubjectTermNames[3] if len(failedSubjectNumsTerm) > 3 else "",
            failedSubjectNumsTerm[4] if len(failedSubjectNumsTerm) > 4 else "",
            failedSubjectTermNames[4] if len(failedSubjectNumsTerm) > 4 else "",
            failedSubjectNumsTerm[5] if len(failedSubjectNumsTerm) > 5 else "",
            failedSubjectTermNames[5] if len(failedSubjectNumsTerm) > 5 else "",
            failedSubjectNumsTerm[6] if len(failedSubjectNumsTerm) > 6 else "",
            failedSubjectTermNames[6] if len(failedSubjectNumsTerm) > 6 else "",
            failedSubjectNumsTerm[7] if len(failedSubjectNumsTerm) > 7 else "",
            failedSubjectTermNames[7] if len(failedSubjectNumsTerm) > 7 else "",
        ])
    create_form(config.SAVE_STUDENT_INFO_FILE_DIR + fileName, FORM_DATA, FORM_HEADER)
    return FileResponse(
    path=config.SAVE_STUDENT_INFO_FILE_DIR + fileName, filename=fileName
    )