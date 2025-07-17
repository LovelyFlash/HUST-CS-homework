import typing as t

from pydantic import BaseModel, Field


class BaseQuery(BaseModel):
    term: str = Field(default="11", description="学期")


class CourseFailedDownload(BaseModel):
    courseName: str = Field(..., description="课程名称")
    # term: str = Field(..., description="学期")
    # major: str = Field(..., description="专业")

class ClassQuery(BaseQuery):
    pass


class CourseQuery(BaseQuery):
    pass


class GradeQuery(BaseModel):
    grade: str = Field(default="21", description="年级")

class StudentInfoConfig(BaseModel):
    grade: str = Field(default="21", description="年级")
    major: str = Field(default="CS", description="专业")
    redRate: float = Field(default=0.33, description="红牌")
    yellowRate: float = Field(default=0.25, description="黄牌")
    requiredCreditExcludePublicElective: float = Field(default=130.0, description="应修学分不含公选")
    requiredCreditIncludePublicElective: float = Field(default=135.0, description="应修学分含公选")

class StudentInfoDownload(BaseModel):
    grade: str = Field(default="21", description="年级")
    red: bool = Field(default=True, description="红牌")
    yellow: bool = Field(default=True, description="黄牌")
    white: bool = Field(default=True, description="普通")
    type: bool = Field(default=False, description="分类方式")

class gradeFile(BaseModel):
    grade: str = Field(default="21", description="年级")
    term: str = Field(default="11", description="学期")