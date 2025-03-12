import os
import re
import typing as t
import json

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
from starlette.responses import FileResponse
from sqlalchemy.orm import Session
from aioredis import Redis
import pandas as pd
import datetime
import random

from database.session import get_db
import models
import schemas
from schemas.basic import Response200, Response400
from database.redis import course_cache, stuInfo_cache
from core.config import config
from .commonCourse import get_each_grade_class_number
from utils.common import to_pinyin, create_form

file_router = APIRouter()


def allowed_file(filename):
    return (
        "." in filename
        and filename.rsplit(".", 1)[1].lower() in config.ALLOWED_EXTENSIONS
    )


@file_router.post("/uploadFile")
async def upload_file(file: UploadFile = File(...)):
    """
    上传并保存文件
    :param files:
    :return:
    """
    try:
        res = await file.read()
        target_dir = "./documents/grade/"
        save_file_name = target_dir + file.filename
        with open(save_file_name, "wb") as fw:
            fw.write(res)
        return Response200(
            msg="文件读取成功",
            data={"filename": file.filename, "file type": file.content_type},
        )
    except Exception as e:
        return Response400(msg="保存文件出现错误：" + str(e))


@file_router.post("/uploadCourseFile")
async def upload_course_file(file: UploadFile = File(...)):
    """
    上传并保存文件
    :param files:
    :return:
    """
    res = await file.read()
    target_dir = "./documents/course/"
    if not re.search(r"[0-9]{2}", file.filename):
        return Response400(msg="文件格式错误")
    save_file_name = (
        target_dir
        + re.search(r"[0-9]{2}", file.filename).group()
        + "_grade_course.xlsx"
    )
    with open(save_file_name, "wb") as fw:
        fw.write(res)
    return Response200(
        msg="文件读取成功",
        data={"filename": file.filename, "file type": file.content_type},
    )

@file_router.post("/uploadScoreFile")
async def upload_score_file(file: UploadFile = File(...)):
    """
    上传并保存文件
    :param files:
    :return:
    """
    try:
        res = await file.read()
        target_dir = "./documents/score/"
        save_file_name = target_dir + file.filename
        with open(save_file_name, "wb") as fw:
            fw.write(res)
        return Response200(
            msg="文件读取成功",
            data={"filename": file.filename, "file type": file.content_type},
        )
    except Exception as e:
        return Response400(msg="保存文件出现错误：" + str(e))


@file_router.post("/uploadFiles/")
async def upload_file(files: t.List[UploadFile] = File(...)):
    """
    多文件上传
    :param files: 文件列表
    :return:
    """
    try:
        fileNameList = []
        for file in files:
            res = await file.read()
            target_dir = "./documents/grade/"
            save_file_name = target_dir + file.filename
            with open(save_file_name, "wb") as fw:
                fw.write(res)
            fileNameList.append(file.filename)
        return Response200(msg="文件读取成功", data={"filename": fileNameList})
    except Exception as e:
        return Response400(msg="保存文件出现错误：" + str(e))


@file_router.get("/xlsxsqls")
async def read_xlsx_to_sql(db: Session = Depends(get_db)):
    """
    目前有两类文件需要读取
    1. 以 S 结尾 ，则为成绩单
        以 A 结尾，则为学业分析
    2. 读入逻辑
        - 读入一条信息，
    :param db:
    :return:
    """
    print("read_xlsx")
    await clearAllData(db)
    fileNames = os.listdir(config.SAVE_FILE_DIR)
    fileNames.sort()
    waitingList = []
    for name in fileNames:
        if not re.match(r"[A-Z]{2,3}[0-9]{4}[SA]{1}[0-9]{2}.xlsx", name):
            waitingList.append(name)
            continue
        result = pd.read_excel(
            config.SAVE_FILE_DIR + name
        )  # 不要加 header 默认都无列名
        term = name[-7:-5]
        major = re.search(r"[A-Z]+", name).group()
        stuClass = re.search(r"[A-Z]+[0-9]+", name).group()
        grade = stuClass[-4:-2]

        if name[-8] == "S":
            await operation_student(db, result, stuClass)
            await operation_courses(db, result, term, grade)
            await operation_scores(db, result, grade, term, major)
            pass
        elif name[-8] == "A":
            await operation_stuAnalysis(result, stuClass, term)
            pass
        print("=" * 50)
        print("finish operate file: " + name)
        print("=" * 50)

    for name in waitingList:
        print("Personal Information File Name: " + name)
        result = pd.read_excel(config.SAVE_FILE_DIR + name)
        await operation_personal_info(db, result)
        print("=" * 50)
        print("finish operate file: " + name)
        print("=" * 50)

    gradeList = (await get_each_grade_class_number(db, await course_cache()))[
        "grade"
    ].keys()
    for grade in gradeList:
        await assignCourseType(db, grade)
    return Response200(msg="导入数据库成功")

@file_router.get("/xlsxsqlspersonal")
async def read_xlsx_to_sql_only_for_person(db: Session = Depends(get_db)):
    print("read_xlsx")
    await clear_calculate_data(db)
    fileNames = os.listdir(config.SAVE_FILE_DIR)
    fileNames.sort()
    waitingList = []
    for name in fileNames:
        if not re.match(r"[A-Z]{2,3}[0-9]{4}[SA]{1}[0-9]{2}.xlsx", name):
            waitingList.append(name)

    for name in waitingList:
        print("Personal Information File Name: " + name)
        result = pd.read_excel(config.SAVE_FILE_DIR + name)
        await operation_personal_info(db, result)
        print("=" * 50)
        print("finish operate file: " + name)
        print("=" * 50)

    gradeList = (await get_each_grade_class_number(db, await course_cache()))[
        "grade"
    ].keys()
    for grade in gradeList:
        await assignCourseType(db, grade)
    return Response200(msg="导入数据库成功")

@file_router.get("/file/flushData")
async def flush_ALL_data(db: Session = Depends(get_db)):
    await clearAllData(db)
    old_dir = config.SAVE_FILE_DIR.strip("/")
    new_dir = datetime.datetime.now().strftime("%Y_%m_%d_%H_%M_%S")
    os.rename(old_dir, old_dir + new_dir)
    os.mkdir(old_dir)
    old_dir = config.SAVE_SCORE_FILE_DIR.strip("/")
    os.rename(old_dir, old_dir + new_dir)
    os.mkdir(old_dir)
    old_dir = config.SAVE_COURSE_FILE_DIR.strip("/")
    os.rename(old_dir, old_dir + new_dir)
    os.mkdir(old_dir)
    return Response200()


@file_router.get("/file/clearCalculateData")
async def clear_calculate_data(db: Session = Depends(get_db)):
    db.query(models.ResultReadState).delete()
    db.commit()
    return Response200()


async def clearAllData(db: Session):
    db.query(models.Students).delete()
    db.query(models.Courses).delete()
    db.query(models.Scores).delete()
    db.query(models.CourseByTermTable).delete()
    db.query(models.ClassByTermChart).delete()
    db.query(models.GradeByTerm).delete()
    db.query(models.MajorChart).delete()
    db.query(models.ResultReadState).delete()
    db.query(models.StudentInfo).delete()
    db.query(models.WeightScores).delete()
    db.commit()
    print("Already clear all data from database...")


@file_router.get("/scoreCalculate")
async def weight_score_calculate(db: Session = Depends(get_db)):
    fileList = os.listdir(config.SAVE_SCORE_FILE_DIR)
    if fileList == None:
        return Response400(msg="未上传平均分文件!")
    for file in fileList:
        res = pd.read_excel(config.SAVE_SCORE_FILE_DIR + file, header=None)
        major = ""
        if "大数据" in file:
            major = "BD"
        elif "本硕博" in file or "启明" in file:
            major = "BSB"
        elif "卓越" in file or "创新" in file:
            major = "ZY"
        elif "物联网" in file:
            major = "IOT"
        elif "校交" in file:
            major = "XJ"
        elif "智能" in file:
            major = "IST"
        elif "计算机" in file:
            major = "CS"
        else:
            major = "ERR"
        print("专业: " + major)
        if major == "ERR":
            print("文件命名错误!")
            return Response400(msg="文件命名错误!")
        await operation_weight_score(db, res, major)
        print("=" * 50)
        print("finish operate file: " + file)
        print("=" * 50)
    Response200()


async def operation_weight_score(db: Session, result: pd.DataFrame, major: str):
    grade = re.search(r"\d{4}", result.iloc[0, 0]).group()[2:]
    idx = 0
    for i in range(result.shape[1]):
        if (not pd.isna(result.iloc[3, i])) and result.iloc[3, i][2:4] == grade and "秋" in result.iloc[3, i]:
            idx = i
            break
    for term in ["11", "12", "21", "22", "31", "32", "41", "42"]:
        if pd.isna(result.iloc[3, idx]):
            break
        for i in range(4, result.shape[0] - 1):
            stuID = result.iloc[i, 1]
            stuName = result.iloc[i, 2]
            res: models.WeightScores = db.query(models.WeightScores).filter(models.WeightScores.stuID == stuID, models.WeightScores.term == term).first()
            if res:
                res.score = float(result.iloc[i, idx])
                db.commit()
                db.refresh(res)
            else:
                score = models.WeightScores(
                    stuID=stuID,
                    stuName=stuName,
                    score=result.iloc[i, idx],
                    term=term,
                    grade=grade,
                    major=major,
                )
                db.add(score)
                db.commit()
                db.refresh(score)
        idx += 1
    term = "ALL"
    for i in range(4, result.shape[0] - 1):
        stuID = result.iloc[i, 1]
        stuName = result.iloc[i, 2]
        res: models.WeightScores = db.query(models.WeightScores).filter(models.WeightScores.stuID == stuID, models.WeightScores.term == term).first()
        if res:
            res.score = float(result.iloc[i, idx])
            db.commit()
            db.refresh(res)
        else:
            score = models.WeightScores(
                stuID=stuID,
                stuName=stuName,
                score=result.iloc[i, idx],
                term=term,
                grade=grade,
                major=major,
            )
            db.add(score)
            db.commit()
            db.refresh(score)


async def operation_personal_info(db: Session, result: pd.DataFrame):
    match = re.search(
        r"院系：(\S+)\s+班级：(\S+)\s+姓名：(\S+)\s+学号：(\S+)\s*", result.iloc[0, 0]
    )
    stuClass = match.group(2).strip()
    stuName = match.group(3).strip()
    stuID = match.group(4).strip()

    # 对班号进行处理
    stuClassNumber = re.search(r"\d+", stuClass).group()[-4:]
    grade = stuClassNumber[-4:-2]

    if "大数据" in stuClass:
        stuClass = "BD" + stuClassNumber
    elif "本硕博" in stuClass or "启明" in stuClass:
        stuClass = "BSB" + stuClassNumber
    elif "卓越" in stuClass or "创新" in stuClass:
        stuClass = "ZY" + stuClassNumber
    elif "物联网" in stuClass:
        stuClass = "IOT" + stuClassNumber
    elif "校交" in stuClass:
        stuClass = "XJ" + stuClassNumber
    elif "智能" in stuClass:
        stuClass = "IST" + stuClassNumber
    elif "计算机" in stuClass:
        stuClass = "CS" + stuClassNumber
    else:
        stuClass = "ERR" + stuClassNumber
    print("班级:" + stuClass)
    print("姓名:" + stuName)
    print("学号:" + stuID)
    res = db.query(models.Students).filter(models.Students.stuID == stuID).first()
    if not res:
        print("在班级成绩单中未找到匹配学生!")
        return
    if res.stuName != stuName or res.stuClass != stuClass:
        stuClass = res.stuClass
        stuName = res.stuName
        print("信息部分不匹配! 经修正后如下:")
        print("班级:" + stuClass)
        print("姓名:" + stuName)
        print("学号:" + stuID)
    for row in result.values[3:]:
        if (not pd.isna(row[0])) and ("加权" in str(row[0])):
            break
        for i in range(len(row) // 4):
            if not pd.isna(row[i * 4]):
                courseName = str(row[i * 4])
                course: models.Courses = (
                    db.query(models.Courses)
                    .filter(
                        models.Courses.courseName == courseName,
                        models.Courses.grade == grade,
                    )
                    .first()
                )
                if not course:
                    course_insert = models.Courses(
                        courseName=courseName,
                        credit=float(row[i * 4 + 2]),
                        term=str(i + 1) + "1",
                        grade=grade,
                        type=(
                            0
                            if pd.isna(row[i * 4 + 3])
                            or ("公选" not in str(row[i * 4 + 3]))
                            else 4
                        ),
                    )
                    db.add(course_insert)
                    db.commit()
                    db.refresh(course_insert)
                score = str(row[i * 4 + 1])
                score = score.split("/")
                if not pd.isna(row[i * 4 + 3]):
                    score.append(str(row[i * 4 + 3]))
                scoreList = []
                for sub in score:
                    sub = str(sub)
                    if sub:
                        if sub.isdigit():
                            scoreList.append(int(sub))
                        elif sub == "优":
                            scoreList.append(90)
                        elif sub == "良":
                            scoreList.append(80)
                        elif sub == "中":
                            scoreList.append(70)
                        elif sub == "及格":
                            scoreList.append(60)
                        elif sub == "差":
                            scoreList.append(59)
                        elif sub == "通过":
                            scoreList.append(80)
                        elif sub == "不通过":
                            scoreList.append(59)
                        elif sub == "缓考":
                            continue
                        else:
                            scoreList.append(0)
                if scoreList == []:
                    continue
                scoreList.sort()
                score_sql: models.Scores = (
                    db.query(models.Scores)
                    .filter(
                        (models.Scores.stuID == stuID)
                        & (models.Scores.courseName == courseName)
                    )
                    .first()
                )
                if score_sql:
                    score_sql.score = max(score_sql.score, scoreList[-1])
                    score_sql.failed = score_sql.failed | (scoreList[0] < 60)
                    db.commit()
                    db.refresh(score_sql)
                    continue
                score_insert = models.Scores(
                    stuID=stuID,
                    courseName=courseName,
                    score=scoreList[-1],
                    failed=(scoreList[0] < 60),
                    major=re.search(r"[A-Z]+", stuClass).group(),
                    grade=grade,
                    term=str(i + 1) + "1" if not course else course.term,
                )
                db.add(score_insert)
                db.commit()
                db.refresh(score_insert)


async def operation_stuAnalysis(db: Session, result, stuClass, term):
    """
    将学业分析写入数据库
    :param result:
    :param garde:
    :param term:
    :return:
    """

    shape = result.shape
    # print(result.shape)
    for i in range(shape[0]):
        tmpRow = result.iloc[i].tolist()
        newRow = [x for x in tmpRow if pd.isna(x) == False]
        # print(len(newRow))
        # print(newRow)
        if len(newRow) == 4:
            # 班长 or 学委
            stuID = newRow[1]
            stuName = newRow[0]
            stuType = ""
            if newRow[2] == "班长":
                stuType = 1
            elif newRow[2] == "学委":
                stuType = 2
            content = newRow[3]
            # print("学委栏")
            # print(stuID,stuType,term,content)
            # stuAnalysis_sql = StuAnalysis.query.filter((StuAnalysis.stuID == stuID) & (StuAnalysis.stuType == stuType) & (StuAnalysis.term == term)).first()
            stuAnalysis_sql = (
                db.query(models.StuAnalysis)
                .filter(
                    (models.StuAnalysis.stuID == stuID)
                    & (models.StuAnalysis.stuType == stuType)
                    & (models.StuAnalysis.term == term)
                )
                .first()
            )
            # print(stuAnalysis_sql)
            if stuAnalysis_sql:
                continue
            else:
                print("insert class commit")
                stuAnalysis_insert = models.StuAnalysis(
                    stuID=stuID,
                    stuName=stuName,
                    stuType=stuType,
                    term=term,
                    stuClass=stuClass,
                    content1=content,
                )
                db.add(stuAnalysis_insert)
                db.commit()
                db.refresh(stuAnalysis_insert)

        elif len(newRow) == 7:
            # 自己
            stuName = newRow[0]
            stuID = newRow[1]
            stuType = 3
            selfContent = newRow[3]
            monitorContent = newRow[4]
            academicContent = newRow[5]
            failSubjectName = newRow[6]
            print("学生栏")
            # print(stuID,stuType,term,grade,selfContent)
            # print(stuID,monitorType,term,grade,monitorContent)
            # print(stuID,academicType,term,grade,academicContent)

            # stuAnalysis_sql_stu = StuAnalysis.query.filter((StuAnalysis.stuID == stuID) & (StuAnalysis.stuType == stuType) & (StuAnalysis.term == term)).first()
            stuAnalysis_sql_stu = (
                db.query(models.StuAnalysis)
                .filter(
                    (models.StuAnalysis.stuID == stuID)
                    & (models.StuAnalysis.stuType == stuType)
                    & (models.StuAnalysis.term == term)
                )
                .first()
            )
            if stuAnalysis_sql_stu:
                continue
            else:
                stuAnalysis_stu = models.StuAnalysis(
                    stuID=stuID,
                    stuName=stuName,
                    stuType=stuType,
                    term=term,
                    stuClass=stuClass,
                    content1=selfContent,
                    content2=monitorContent,
                    content3=academicContent,
                    failSubjectName=failSubjectName,
                )
                db.add(stuAnalysis_stu)
                db.commit()
                db.refresh(stuAnalysis_stu)

    # print("=" * 50)
    # print("finish operation stuanalysis")
    # print("=" * 50)


async def operation_scores(db: Session, result, grade, term, major):
    """
    将学生成绩写入数据库
    :param result:
    :param term:
    :return:
    """
    coursers = result.iloc[2].tolist()
    coursersNew = [x for x in coursers if pd.isna(x) == False]
    credits = result.iloc[3].tolist()
    creditsNew = [x for x in credits if pd.isna(x) == False]
    len_course = len(creditsNew)
    courseNames = coursersNew[:len_course]
    shape = result.shape
    for i in range(3, shape[0]):
        stuScore = result.iloc[i].tolist()
        if str(stuScore[0])[0] == "U":
            stuID = stuScore[0]
            stuScoreNum = stuScore[2 : 2 + len_course]
            for courseName, score in zip(courseNames, stuScoreNum):
                if pd.isna(score) == False:
                    score = str(score)
                    scoreList = []
                    for sub in score.split("/"):
                        sub = str(sub)
                        if sub:
                            if sub.isdigit():
                                scoreList.append(int(sub))
                            elif sub == "优":
                                scoreList.append(90)
                            elif sub == "良":
                                scoreList.append(80)
                            elif sub == "中":
                                scoreList.append(70)
                            elif sub == "及格":
                                scoreList.append(60)
                            elif sub == "差":
                                scoreList.append(59)
                            elif sub == "通过":
                                scoreList.append(80)
                            elif sub == "不通过":
                                scoreList.append(59)
                            elif sub == "缓考":
                                continue
                            else:
                                scoreList.append(0)
                    if scoreList == []:
                        continue
                    scoreList.sort()
                    score_sql: models.Scores = (
                        db.query(models.Scores)
                        .filter(
                            (models.Scores.stuID == stuID)
                            & (models.Scores.courseName == courseName)
                        )
                        .first()
                    )
                    if score_sql:
                        score_sql.score = max(score_sql.score, scoreList[-1])
                        score_sql.failed = score_sql.failed | (scoreList[0] < 60)
                        db.commit()
                        db.refresh(score_sql)
                        continue
                    score_insert = models.Scores(
                        stuID=stuID,
                        courseName=courseName,
                        score=scoreList[-1],
                        failed=(scoreList[0] < 60),
                        major=major,
                        grade=grade,
                        term=term,
                    )
                    db.add(score_insert)
                    db.commit()
                    db.refresh(score_insert)

    # print("=" * 50)
    # print("finish operation_scores")
    # print("=" * 50)


@file_router.post("/download/course")
async def download_Course_File(queryItem: schemas.GradeQuery):
    courseFileName = str(queryItem.grade) + "_grade_course.xlsx"
    return FileResponse(
        path=config.SAVE_COURSE_FILE_DIR + courseFileName, filename=courseFileName
    )


@file_router.get("/courseCalculate")
async def course_calculate(db: Session = Depends(get_db)):
    gradeList = (await get_each_grade_class_number(db, await course_cache()))[
        "grade"
    ].keys()
    for grade in gradeList:
        await assignCourseType(db, grade)
    return Response200()


async def assignCourseType(db: Session, grade) -> str:
    print("=" * 50)
    print("assign course type for grade" + grade)
    key = "studentInfo_" + str(grade)
    db.query(models.ResultReadState).filter(models.ResultReadState.key == key).delete()
    db.commit()
    courseFileList = os.listdir(config.SAVE_COURSE_FILE_DIR)
    courseFileName = str(grade) + "_grade_course.xlsx"
    courseList = []
    courseDict = {}
    if courseFileName in courseFileList:
        result = pd.read_excel(config.SAVE_COURSE_FILE_DIR + courseFileName).iloc[1:]
        for i in range(len(result)):
            courseList.append([result.iloc[i, 0], result.iloc[i, 1]])
            courseDict[str(result.iloc[i, 0])] = result.iloc[i, 1]
    res: list[models.Courses] = (
        db.query(models.Courses).filter(models.Courses.grade == grade).all()
    )
    res.sort(key=lambda x: to_pinyin(x.courseName))
    for course in res:
        if course.courseName in courseDict.keys():
            db.query(models.Courses).filter(
                models.Courses.courseName == course.courseName,
                models.Courses.grade == grade,
            ).update({"type": courseDict[course.courseName]})
            db.commit()
        else:
            courseDict[course.courseName] = course.type
            courseList.append([course.courseName, course.type])
    FORM_HEADER = ["课程名", "类型"]
    FORM_DATA = []
    FORM_DATA.append(["0:未分类,1:公共必修,2:专业必修,3:专业选修,4:人文选修", ""])
    courseList.sort(key=lambda x: to_pinyin(x[0]))
    for item in courseList:
        FORM_DATA.append(item)
    create_form(config.SAVE_COURSE_FILE_DIR + courseFileName, FORM_DATA, FORM_HEADER)
    print("=" * 20 + "complete" + "=" * 22)
    return courseFileName


async def operation_courses(db: Session, result, term, grade):
    """
    将课程信息写入数据库
    :param result:
    :param term:
    :return:
    """
    coursers = result.iloc[2].tolist()
    coursersNew = [x for x in coursers if pd.isna(x) == False]
    credits = result.iloc[3].tolist()
    creditsNew = [x for x in credits if pd.isna(x) == False]
    for x, y in zip(coursersNew, creditsNew):
        course_sql = (
            db.query(models.Courses)
            .filter(
                models.Courses.courseName == x,
                models.Courses.term == term,
                models.Courses.grade == grade,
            )
            .first()
        )
        if course_sql:
            continue
        else:
            course = models.Courses(
                courseName=x, credit=y, term=term, grade=grade, type=0
            )
            db.add(course)
            db.commit()
            db.refresh(course)

    # print("=" * 50)
    # print("finish commit course")
    # print("=" * 50)


async def operation_student(db: Session, result, stuClass):
    """
    将学生信息写入数据库
    :param result: pandas读入的成绩单数据
    :return:
    """
    # 课程名称 & 学分
    # 学号
    stuIDList = result.iloc[:, [0]].values
    stuIDList = stuIDList.reshape(-1)
    stuNewIDList = [x for x in stuIDList if pd.isna(x) == False]
    stuNewIDList = stuNewIDList[2:]
    # 姓名
    stuNameList = result.iloc[:, [1]].values
    stuNameList = stuNameList.reshape(-1)
    stuNewNameList = [x for x in stuNameList if pd.isna(x) == False]
    for x, y in zip(stuNewIDList, stuNewNameList):
        student_sql = (
            db.query(models.Students).filter(models.Students.stuID == x).first()
        )

        if student_sql:
            continue
        else:
            student = models.Students(stuID=x, stuName=y, stuClass=stuClass)
            db.add(student)
            db.commit()

    # print("=" * 50)
    # print("finish operation_scores")
    # print("=" * 50)

def directory_check():
    if not os.path.exists(config.SAVE_ROOT_DIR):
        os.makedirs(config.SAVE_ROOT_DIR)
    if not os.path.exists(config.SAVE_FILE_DIR):
        os.makedirs(config.SAVE_FILE_DIR)
    if not os.path.exists(config.SAVE_COURSE_FILE_DIR):
        os.makedirs(config.SAVE_COURSE_FILE_DIR)
    if not os.path.exists(config.SAVE_SCORE_FILE_DIR):
        os.makedirs(config.SAVE_SCORE_FILE_DIR)
    if not os.path.exists(config.SAVE_FAILED_STUDENT_BY_TERM_FILE_DIR):
        os.makedirs(config.SAVE_FAILED_STUDENT_BY_TERM_FILE_DIR)
    if not os.path.exists(config.SAVE_STUDENT_INFO_FILE_DIR):
        os.makedirs(config.SAVE_STUDENT_INFO_FILE_DIR)
    if not os.path.exists(config.SAVE_FAILED_STUDENT_BY_COURSE_FILE_DIR):
        os.makedirs(config.SAVE_FAILED_STUDENT_BY_COURSE_FILE_DIR)

directory_check()
