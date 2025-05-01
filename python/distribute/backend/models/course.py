from sqlalchemy import Boolean, Column, Integer, String,Float


from .base import Base

class Courses(Base):
    __tablename__ = 'courses'
    courseName = Column(String(30), primary_key=True)
    credit = Column(Float, nullable=False)
    term = Column(Integer, primary_key=True)
    grade = Column(String(5), primary_key=True)
    type = Column(Integer, nullable=False, default=0)
    #type: 0-其他、1-公共必修、2-专业必修、3-专业选修、4-公共选修、5-重修课程