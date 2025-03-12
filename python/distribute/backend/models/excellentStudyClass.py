from sqlalchemy import Boolean, Column, Integer, String


from .base import Base

class ExcellentStudyClass(Base):
    __tablename__ = 'excellentStudyClass'
    grade = Column(Integer,primary_key=True)
    year = Column(Integer,primary_key=True)
    totalClassNum = Column(Integer)
    excellentClassNum = Column(Integer)

    def to_dict(self):
        d = {
            "grade":self.grade,
            "year":self.year,
            "totalClassNum":self.totalClassNum,
            "excellentClassNum":self.excellentClassNum
        }
        return d

    def __str__(self):
        return str(
            {
                "grade": self.grade,
                "year": self.year,
                "totalClassNum": self.totalClassNum,
                "excellentClassNum": self.excellentClassNum
            }
        )
