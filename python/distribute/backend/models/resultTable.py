from sqlalchemy import Boolean, Column, Integer, String, Float
from sqlalchemy.dialects.mysql import LONGTEXT

from .base import Base


class ResultReadState(Base):
    __tablename__ = "resultReadState"
    key = Column(String(100), primary_key=True)


class CourseByTermTable(Base):
    """
    班级维度数据表
    {
        "id": "term"+str(term),
        "term": "11",
        "courseName": "C++程序设计",
        "failed_nums": {
            "18": 2,
            "19": 0,
            "20": 2,
            "21": 0
        },
        "gradeDistribute": {
            "18": {
                "0-59": 2,
                "60-69": 1,
                "70-79": 4,
                "80-89": 15,
                "90-100": 28
            },
            "19": {
                "0-59": 0,
                "60-69": 0,
                "70-79": 1,
                "80-89": 0,
                "90-100": 0
            },
            "20": {
                "0-59": 2,
                "60-69": 1,
                "70-79": 5,
                "80-89": 3,
                "90-100": 11
            },
            "21": {
                "0-59": 0,
                "60-69": 0,
                "70-79": 0,
                "80-89": 0,
                "90-100": 5
            }
        },
        "pass_rate": {
            "18": 1,
            "19": 0,
            "20": 1,
            "21": 0
        },
        "failStudentsList":[
                            ["年级","班级","姓名"]
        ],
        "sumFailedNums": 4
    }

    "courseName": courseName,
    "failed_nums": {},
    "gradeDistribute": {},
    "pass_rate": {},
    "failStudentsList": [],
    "sumFailedNums": 0
    """

    __tablename__ = "courseByTermTable"
    id = Column(String(10), primary_key=True)
    term = Column(String(2), primary_key=True)
    courseName = Column(String(100), primary_key=True)
    major = Column(String(5), primary_key=True)
    failed_nums = Column(String(255), nullable=False)
    gradeDistribute = Column(LONGTEXT, nullable=False)
    pass_rate = Column(String(255), nullable=False)
    failStudentsList = Column(LONGTEXT)
    sumFailedNums = Column(Integer, nullable=False)


class ClassByTermTable(Base):
    """
    班级维度数据表
    {
            "className": "ZY1801",
            "totalNum": 28,
            "failedNum": 0,# 挂科人数
            "failedThreeNum": 0,
            "failedNum2": 0,# 挂科人次
            "failedRate": 0.0,
            "failedRange": 0,# 挂科幅度
            "term":11
    }
    """

    __tablename__ = "classByTermTable"
    className = Column(String(30), primary_key=True)
    term = Column(String(2), primary_key=True)
    totalNum = Column(Integer, nullable=False)
    failedNum = Column(Integer, nullable=False)
    failedThreeNum = Column(Integer, nullable=False)
    failedNum2 = Column(Integer, nullable=False)
    failedRate = Column(Float, nullable=False)
    failedRange = Column(Float, nullable=False)


class ClassByTermChart(Base):
    """
    班级维度数据 图
    {
            "term": "11",
            "grade": "18",
            "classNameList": [
                    "卓越\n1801",
                    "ACM\n1801",
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
    """

    __tablename__ = "classByTermChart"
    term = Column(String(30), primary_key=True)
    grade = Column(String(2), primary_key=True)
    type = Column(Boolean, primary_key=True)  # False: major, True: class.
    classNameList = Column(LONGTEXT, nullable=False)
    failedNum = Column(LONGTEXT, nullable=False)
    failedRate = Column(LONGTEXT, nullable=False)
    totalNum = Column(LONGTEXT, nullable=False)


class MajorChart(Base):
    """
    专业维度数据 图
    {
            "term": "11",
            "major": "ALL",
            "classNameList": [
                    "卓越\n1801",
                    "ACM\n1801",
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
    """

    __tablename__ = "majorChart"
    major = Column(String(5), primary_key=True)
    gradeNameList = Column(LONGTEXT, nullable=False)
    gradeFailedNum = Column(String(255), nullable=False)
    gradeFailedRate = Column(String(255), nullable=False)
    gradeTotalNum = Column(String(255), nullable=False)
    classNameList = Column(LONGTEXT, nullable=False)
    failedNum = Column(LONGTEXT, nullable=False)
    failedRate = Column(LONGTEXT, nullable=False)
    totalNum = Column(LONGTEXT, nullable=False)
    showLabel = Column(String(255), nullable=False)


class GradeByTerm(Base):
    """
    年级维度数据 柱状图
    {
        "courseName": [
            "信息技术导论",
            "微积分︵一︶︵上︶",
            "C语言程序设计",
            "中国语文",
            "综合英语︵一︶"
        ],
        "failed_nums": [
            9,
            8,
            5,
            3,
            3,
            1
        ],
        "failed_rates": [
            "2.26",
            "2.01",
            "1.25",
            "0.75",
            "0.75",
            "0.25"
        ],
        "grade": 18,
        "term":11
    }
    """

    __tablename__ = "gradeByTerm"

    term = Column(String(2), primary_key=True)
    grade = Column(String(2), primary_key=True)
    courseName = Column(LONGTEXT, nullable=False)
    failed_nums = Column(String(200), nullable=False)
    failed_rates = Column(String(200), nullable=False)


class WeightScoreByTerm(Base):
    
    __tablename__ = "weightScoreByTerm"

    grade = Column(String(5), primary_key=True)
    term = Column(String(5), primary_key=True)
    major = Column(String(5), primary_key=True)
    info = Column(LONGTEXT, nullable=False)


class StudentInfoConfig(Base):
    __tablename__ = "studentInfoConfig"
    grade = Column(String(2), primary_key=True)
    major = Column(String(5), primary_key=True)
    redRate = Column(Float, nullable=False)
    yellowRate = Column(Float, nullable=False)
    requiredCreditExcludePublicElective = Column(Float, nullable=False)
    requiredCreditIncludePublicElective = Column(Float, nullable=False)


class StudentInfo(Base):
    """
    某个年级所有不及格学生的信息
    {
        "stuID": "U201814525",
        "grade":19,
        "stuName": "孙潋瑜",
        "stuClass": "CS1906",
        "totalWeightedScore": 16.8,
        "failedSubjectNames": "JAVA 语言程序设计,JAVA 语言程序设计实验,Verilog语言,信号与线性系统,复变函数与积分变换,大学物理（二）,操作系统原理,操作系统原理实验,数值分析,数字电路与逻辑设计实验,数字电路与逻辑设计（一）,数据结构,数据结构实验,概率论与数理统计,模拟电子技术（二）,毛泽东思想和中国特色社会主义理论体系概论,汇编语言程序设计,汇编语言程序设计实践,物理实验（二）,电路理论（五）,离散数学（二）,程序设计综合课程设计,算法设计与分析,算法设计与分析实践,计算机组成原理,计算机组成原理实验,计算机通信与网络,计算机通信与网络实践,软件工程",
        "failedSubjectNums": 29,
        "sumFailedCredit": 10.5,
        "totalCredit": 20,
        ...
        "failedSubjectNumsTerm": [
            16,
            3,
            10,
            0
        ],
        "totalWeightedScoreTerm": [
            18.58,
            4.71,
            15.65,
            0
        ],


    },,
    """

    __tablename__ = "studentInfo"

    stuID = Column(String(10), primary_key=True)
    grade = Column(String(2), nullable=False)
    stuName = Column(String(50), nullable=False)
    stuClass = Column(String(10), nullable=False)
    totalWeightedScore = Column(Float, nullable=True)
    failedSubjectNames = Column(LONGTEXT, nullable=True)
    failedSubjectTermNames = Column(LONGTEXT, nullable=True)
    failedSubjectNums = Column(Integer, nullable=True)
    sumFailedCreditALL = Column(Float, nullable=True)  # 全部
    totalCreditALL = Column(Float, nullable=True)
    sumFailedCreditUnclassified = Column(Float, nullable=True)  # type=0 未分类
    totalCreditUnclassified = Column(Float, nullable=True)
    sumFailedCreditPublicCompulsory = Column(Float, nullable=True)  # type=1 公共必修
    totalCreditPublicCompulsory = Column(Float, nullable=True)
    sumFailedCreditProfessionalCompulsory = Column(
        Float, nullable=True
    )  # type=2 专业必修
    totalCreditProfessionalCompulsory = Column(Float, nullable=True)
    sumFailedCreditProfessionalElective = Column(
        Float, nullable=True
    )  # type=3 专业选修
    totalCreditProfessionalElective = Column(Float, nullable=True)
    sumFailedCreditPublicElective = Column(Float, nullable=True)  # type=4 公共选修
    totalCreditPublicElective = Column(Float, nullable=True)
    failedSubjectNumsTerm = Column(String(255), nullable=True)  # 每学年挂科数量
    totalWeightedScoreTerm = Column(String(255), nullable=True)  # 每学加权平均分
    totalFailedCreditTerm = Column(String(255), nullable=True)
    totalCreditExcludePublicElective = Column(Float, nullable=True)
    totalCreditIncludePublicElective = Column(Float, nullable=True)
    requiredCreditExcludePublicElective = Column(Float, nullable=True)
    requiredCreditIncludePublicElective = Column(Float, nullable=True)
    excludePublicElectiveType = Column(Integer, nullable=True)
    includePublicElectiveType = Column(Integer, nullable=True)
