from sqlalchemy import Boolean, Column, Integer, String


from .base import Base


class Students(Base):
    __tablename__ = "students"
    
    stuID = Column(String(10), primary_key=True)
    stuName = Column(String(20), nullable=False)
    stuClass = Column(String(8), nullable=False)

    def to_dic(self):
        """返回一个用户信息字典接口，方便外界调用"""
        consoler_info = {
            "stuID": self.stuID,
            "stuName": self.stuName,
            "stuClass": self.stuClass,
        }
        return consoler_info
