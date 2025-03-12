from pydantic import BaseModel,Field

class StudentInfoQuery(BaseModel):
    stuID : str = Field(default=None,description="学生学号")
    stuName: str = Field(default="",description="学生姓名")