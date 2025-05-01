from fastapi import Depends, HTTPException, status
import jwt
from jwt import PyJWTError

import schemas
import models
from database.curd import get_user_by_cID, create_user,get_user_by_cName
from database.session import get_db
from core import security
from core import config
from database import session


# async def get_current_user(
#         db=Depends(session.get_db), token: str = Depends(security.oauth2_scheme)
# ):
#     credentials_exception = HTTPException(
#         status_code=status.HTTP_401_UNAUTHORIZED,
#         detail="Could not validate credentials",
#         headers={"WWW-Authenticate": "Bearer"},
#     )
#     try:
#         payload = jwt.decode(
#             token, config.SECRET_KEY, algorithms=[config.ALGORITHM]
#         )
#         cName: str = payload.get("sub")
#         if cName is None:
#             raise credentials_exception
#         permissions: str = payload.get("permissions")
#         token_data = schemas.TokenData(cName=cName, permissions=permissions)
#     except PyJWTError:
#         raise credentials_exception
#     user = get_user_by_cName(db, token_data.cName)
#     if user is None:
#         raise credentials_exception
#     return user


# async def get_current_active_user(
#         current_user: models.User = Depends(get_current_user),
# ):
#     if not current_user.is_active:
#         raise HTTPException(status_code=400, detail="Inactive user")
#     return current_user
#
#
# async def get_current_active_superuser(
#         current_user: models.User = Depends(get_current_user),
# ) -> models.User:
#     if not current_user.is_superuser:
#         raise HTTPException(
#             status_code=403, detail="The user doesn't have enough privileges"
#         )
#     return current_user

def authenticate_user_cID(db, cID: str, password: str):
    user = get_user_by_cID(db, cID)
    if not user:
        return False
    if not security.verify_password(password, user.hashed_password):
        return False
    return user

def authenticate_user(db, cName: str, password: str):
    print("authenticate_user:{}".format(cName))
    user = get_user_by_cName(db, cName)
    if not user:
        return False
    print("user:{}".format(user.cID))
    if not security.verify_password(password, user.hashed_password):
        return False
    return user


def sign_up_new_user(db, cName: str, password: str):
    user = get_user_by_cName(db, cName)
    if user:
        return False  # User already exists
    new_user = create_user(
        db,
        schemas.UserCreate(
            cName=cName,
            password=password,
            is_active=True,
            is_superuser=False,
        ),
    )
    return new_user

async def check_permission():
    """
    权限验证
    
    """