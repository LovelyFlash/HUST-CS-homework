import typing as t

from fastapi import APIRouter,Depends,Response,Request,status
from fastapi.security import OAuth2PasswordBearer
from fastapi.requests import Request

import schemas
from schemas import Response400,Response200
from core import get_password_hash,create_access_token
from database.session import get_db
from database.curd import get_users,create_user,get_user_by_cID

user_router = APIRouter(tags=["用户管理"])

@user_router.get("/users",response_model=t.List[schemas.User],response_model_exclude_none=True)
async def users_list(response:Response,db=Depends(get_db)):
    """
    get all user
    :param response:
    :param db:
    :return:
    """
    users = get_users(db)
    return users

@user_router.post("/users",response_model=t.Union[schemas.Response200,Response400],response_model_exclude_none=True)
async def user_create(request:Request,user:schemas.UserCreate,db=Depends(get_db)):
    """
    新建一个用户
    :param request:
    :param user:
    :param db:
    :return:
    """
    db_user = get_user_by_cID(db,user.cID)
    if db_user:
        return Response200(code=status.HTTP_201_CREATED,msg="用户已经存在在数据库中")
    return Response200(code=status.HTTP_200_OK,data=create_user(db,user),msg="创建成功")