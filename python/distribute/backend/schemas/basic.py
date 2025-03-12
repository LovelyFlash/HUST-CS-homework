from typing import Any
from enum import Enum

from pydantic import BaseModel,Field
from fastapi import status

class CodeEnum(int,Enum):
    """

    """

class ResponseBasic(BaseModel):
    code: int = Field(default=status.HTTP_200_OK,description="返回状态码")
    msg: str = Field(default="请求成功",description="提示信息")
    data: Any = Field(default="",description="数据结果")

class Response200(ResponseBasic):
    pass

    def to_dict():
        pass

class Response400(ResponseBasic):
    code: int = Field(default=status.HTTP_400_BAD_REQUEST)
    msg : str = "请求失败"


class ResponseToken(Response200):
    access_token: str
    token_type: str = Field(default="bearer")