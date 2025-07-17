from fastapi.security import OAuth2PasswordBearer
from passlib.context import CryptContext
from datetime import datetime, timedelta
from typing import Optional
import jwt


from .config import config


# oauth2_scheme = OAuth2PasswordBearer(tokenUrl="/api/v1/token")

pwd_context = CryptContext(schemes=['bcrypt'],deprecated="auto")

def get_password_hash(password:str) ->str:
    return pwd_context.hash(password)

def verify_password(plain_password:str,hashed_password:str)-> bool:
    return pwd_context.verify(plain_password,hashed_password)

def create_access_token(data: dict, expires_delta: Optional[timedelta] = None):
    """
    生成token
    :param data: 字典
    :param expires_delta: 有效时间
    :return:
    """
    to_encode = data.copy()
    if expires_delta:
        expire = datetime.utcnow() + expires_delta
    else:
        expire = datetime.utcnow() + timedelta(minutes=15)
    to_encode.update({"exp": expire})
    encoded_jwt = jwt.encode(to_encode, config.SECRET_KEY, algorithm=config.ALGORITHM)
    return encoded_jwt