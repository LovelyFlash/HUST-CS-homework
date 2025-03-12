from sqlalchemy import Boolean, Column, Integer, String,ForeignKey


from .base import Base

class FileDB(Base):

    __tablename__ = "filedb"

    id = Column(Integer,primary_key=True,index=True)
    fileName = Column(String(40),nullable=False)
    md5 = Column(String(10),nullable=False)
    # owner_id = Column(String(10),ForeignKey('user.cID'),nullable=False)
    owner_id = Column(String(10),  nullable=False)
    fileType = Column(String(3))

