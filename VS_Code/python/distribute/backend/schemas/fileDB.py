import typing as t

from pydantic import BaseModel,Field

class FileBase(BaseModel):
    md5: str
    fileName: str
    owner_id: int
    fileType: t.Optional[str]


class FileCreate(FileBase):
    """
    用于向数据库提交新纪录
    """
    pass

class FileInfo(FileBase):
    """
    用于从数据库中查询结果
    """
    id:int
    class Config:
        from_attributes = True
