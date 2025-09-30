from sqlalchemy import Boolean, Column, Integer, String, Float


from .base import Base

class Scores(Base):
    __tablename__ = 'scores'
    stuID = Column(String(10),primary_key=True)
    courseName = Column(String(30), primary_key=True)
    score = Column(Integer, nullable=False)
    failed = Column(Boolean, nullable=False)
    major = Column(String(5)) # 专业
    grade = Column(String(10)) # 年级
    term = Column(Integer)

    def to_dic(self):
        return {
            "stuID":self.stuID,
            "courseName": self.courseName,
            "score": self.score,
            "major": self.major,
            "grade": self.grade,
            "term": self.term
        }

class WeightScores(Base):
    
    __tablename__ = "weightScores"
    stuID = Column(String(10),primary_key=True)
    stuName = Column(String(10),nullable=False)
    score = Column(Float,nullable=False)
    term = Column(String(5),primary_key=True)
    grade = Column(String(10),nullable=False) # 年级
    major = Column(String(5),nullable=False)
