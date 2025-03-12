from sqlalchemy import Boolean, Column, Integer, String, DateTime,ForeignKey
from sqlalchemy.orm import relationship

from werkzeug.security import generate_password_hash,check_password_hash
from sqlalchemy.sql import func
from datetime import datetime 

from .base import Base

class User(Base):
    """用户"""
    __tablename__ = 'user'
# todo:删除cID,级联
    cID = Column(String(10), primary_key=True,comment="工号")
    cName = Column(String(50), nullable=False, primary_key=True)
    hashed_password = Column(String(200), nullable=False) # 加密的。生成的会比较长
    is_active = Column(Boolean,default=True)
    is_superuser = Column(Boolean,default=True)
    # type = db.Column(db.String(200),nullable=False)


# class Role(Base):
#     """角色"""
#     __tablename__ = 'role'
    
#     id = Column(Integer,autoincrement=True)
    
#     roleName = Column(String(50), nullable=False, primary_key=True)
#     create_time = Column(DateTime,default=datetime.now,comment="创建时间") # 创建时间'
#     update_time = Column(auto_now=True, onupdate=datetime.now, default=datetime.now) # 更新时间"
#     role_status = Column(Boolean,default=False, comment="角色状态 True:启用") 
#     role_desc= Column(String(20),nullable=True, comment="角色描述")
#     access = Column()
#     cID = relationship("User", backref="cID",)

# class Access(Base):
#     """权限"""
    
#     __tablename__ = "access"
#     cID = Column(String(10), primary_key=True,comment="工号")
#     accessName = Column(String(20),comment="权限名称") 
#     parent_id = Column(Integer, default=0, comment="父id") # 权限查询树
#     scopes = Column(String(20),unique=True, comment="权限范围标识")
#     accessDes = Column(String(50),comment="权限描述")
#     is_check = Column(Boolean, default=False, comment="是否验证权限 True：验证") # 即用户处于激活状态
#     is_menu = Column(Boolean, default=False, comment="是否为菜单 True：是")
    
    
