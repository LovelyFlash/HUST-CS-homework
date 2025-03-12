import typing as t

from pydantic import BaseModel,Field

class ExcellentStudyClassSchemas(BaseModel):
    grade: int = Field(...,description="年级 如 20")
    year: int = Field(...,description="年份 如 2022")
    excellentClassNum : int = Field(default=0,description="所有优良学风班级数量")
    totalClassNum: int = Field(default=0,description="所有班级数量")