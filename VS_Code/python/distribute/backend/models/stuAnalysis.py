from sqlalchemy import Boolean, Column, Integer, String
from sqlalchemy.dialects.mysql import LONGTEXT

from .base import Base

class StuAnalysis(Base):
    __tablename__ = 'stuanalysis'
    stuID = Column(String(10), primary_key=True)
    stuName = Column(String(20), nullable=False)
    stuType = Column(Integer, primary_key=True)  # 班长:1 学委:2 自己:3
    term = Column(Integer, primary_key=True) # 11 12 21 22
    failSubjectName = Column(String(200)) # 不及格科目名称
    stuClass = Column(String(10))
    content1 = Column(String(850)) # 自己
    content2 = Column(String(850))  # 班长
    content3 = Column(String(850))  # 学委

    def to_dic(self):
        d = {
            "stuID":self.stuID,
            "stuName": self.stuName,
            "stuType": self.stuType,
            "term": self.term,
            "failSubjectName": self.failSubjectName,
            "stuClass": self.stuClass,
            "content1": self.content1,
            "content2": self.content2,
            "content3": self.content3
        }
        return d