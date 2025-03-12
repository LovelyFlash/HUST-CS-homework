from fastapi import HTTPException,status
from sqlalchemy.orm import Session
import typing as t

import models
import schemas
from core import get_password_hash
from schemas.user import UserOut

def get_user_by_cID(db:Session,cID:str):
    return db.query(models.User).filter(models.User.cID == cID).first()

def get_user_by_cName(db:Session,cName:str):
    return db.query(models.User).filter(models.User.cName == cName).first()

def get_users(db:Session,skip:int = 0,limit:int = 100) -> t.List[UserOut]:
    return db.query(models.User).offset(skip).limit(limit).all()


def get_user(db:Session,cID:str):
    user = db.query(models.User).filter(models.User.cID == cID).first()
    if not user:
        raise HTTPException(status_code=status.HTTP_404_NOT_FOUND,detail="user not found")
    return user

def create_user(db:Session,user:schemas.UserCreate):
    hashed_password = get_password_hash(user.password)
    db_user = models.User(
        cID=user.cID,
        cName=user.cName,
        hashed_password=hashed_password,
        is_active=user.is_active,
        is_superuser=user.is_superuser
    )
    db.add(db_user)
    db.commit()
    db.refresh(db_user)
    return UserOut(cID=db_user.cID,cName=db_user.cName,is_active=db_user.is_active,is_superuser=db_user.is_superuser)




if __name__ == '__main__':
    print(get_password_hash('jzj123'))