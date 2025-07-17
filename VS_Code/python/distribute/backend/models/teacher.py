from sqlalchemy import Boolean, Column, Integer, String


from .base import Base

class Teacher(Base):
    __tablename__ = 'teachers'
    # userid = Column(Integer, primary_key=True, autoincrement=True)
    tID = Column(String(8), primary_key=True)
    tCourse = Column(String(20), nullable=False)
    tClass = Column(String(10), nullable=False)