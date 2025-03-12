from fastapi import HTTPException,status
from sqlalchemy.orm import Session
from sqlalchemy import  and_,or_


import models


async def ec_get_info_by_grade_year(db:Session,grade,year):
    """

    :param db:
    :param grade:
    :param year:
    :return:
    """
    res = db.query(models.ExcellentStudyClass).filter(and_(models.ExcellentStudyClass.grade == grade,models.ExcellentStudyClass.year==year)).first()
    return res

async def ec_getYearList(db:Session):
    """
    从数据库中获取年份数据
    :param db:
    :return:
    """
    yearList = db.query(models.ExcellentStudyClass).with_entities(models.ExcellentStudyClass.year).all()
    yearList = [year[0] for year in yearList]
    yearList = list(set(yearList))
    yearList.sort()

    return yearList

async def ec_getGradeList(db:Session):
    """
    从数据库中获取年级数据
    :return:
    """
    gradeList = db.query(models.ExcellentStudyClass).with_entities(models.ExcellentStudyClass.grade).all()
    gradeList = [grade[0] for grade in gradeList]
    gradeList = list(set(gradeList))
    gradeList.sort()
    print(gradeList)
    return gradeList

async def ec_gradeToYear(grade):
    """
    年份转换
    :param grade:
    :return:
    """
    return 2000 + grade

async def ec_get_by_year(db:Session,year):
    """

    :param year:
    :return:
    {
        "2018":{
            "excellentStudyClassNum":13,
            "totalClassNum":24
        }
    }
    """

    res = db.query(models.ExcellentStudyClass).filter(models.ExcellentStudyClass.year == year).all()
    res_dict ={
        "excellentStudyClassNum":0,
        "totalClassNum": 0
    }
    for row in res:
        res_dict["excellentStudyClassNum"] += row.excellentClassNum
        res_dict["totalClassNum"] += row.totalClassNum

    return res_dict


async def ec_getCurrentYear():
    """
    获取当年年份
    :return:
    """
    # 优化格式化化版本
    import time
    print(time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(time.time())))
    return time.strftime('%Y',time.localtime(time.time()))

async def ec_get_by_grade(db:Session,grade):
    """

    :param grade:
    :return:
    {
        “16”：{
            “grade1”:{
                "excellentClassNum":8,
                "excellentRate":23.0
            },
            "grade2":{
                "excellentClassNum":8,
                "excellentRate":23.0
            },
            "grade3":{
                "excellentClassNum":8,
                "excellentRate":23.0
            }
        }
    }
    """
    res = db.query(models.ExcellentStudyClass).filter(models.ExcellentStudyClass.grade == grade).order_by(models.ExcellentStudyClass.year).all()
    res_arr = {
        str(grade):{}
    }

    for row in res:
        res_arr[str(grade)]["grade"+str(row.year - (2000+row.grade))] = {
            "totalClassNum": row.totalClassNum,
            "excellentClassNum": row.excellentClassNum,
            "excellentRate":(round(row.excellentClassNum*1.0/row.totalClassNum*100,2)) if row.totalClassNum != 0 else 0
        }

    return res_arr[str(grade)]
