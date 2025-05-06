from fastapi import Depends, HTTPException
from fastapi.security import OAuth2PasswordBearer
from fastapi import status
from jose import jwt, JWTError
from fastapi.requests import Request

from.config import config
from models import User
from database.session import get_db

# 客户端会向该URL发送username和password参数，然后得到一个token值
# 并不会创建相应的URL路径操作，只是指明了客户端用来获取token的目标URL。
oauth2_scheme = OAuth2PasswordBearer(tokenUrl="apis/v1/login")


# oauth2_scheme()
async def get_current_user(request: Request, token: str = Depends(oauth2_scheme),db=Depends(get_db)) -> User:
# async def get_current_user(request: Request, token: str = Depends(oauth2_scheme)) -> User:
    """
    # oauth2_scheme -> 从请求头中取到 Authorization 的value
    解析token 获取当前用户对象
    :param token: 登录之后获取到的token
    :return: 当前用户对象
    """
    credentials_exception = HTTPException(
        status_code=status.HTTP_401_UNAUTHORIZED,
        detail="Could not validate credentials",
        headers={"WWW-Authenticate": "Bearer"},
    )
    try:
        payload = jwt.decode(
            token, config.SECRET_KEY, algorithms=[
                config.ALGORITHM])
        print("="*50)
        print(payload)
        username: str = payload.get("sub", None)
        if username is None:
            raise credentials_exception
    except JWTError:
        raise credentials_exception
    print("="*50)
    print(username)
    # user = await User.get(username=username)
    # db = get_db()
    user = db.query(User).filter(User.cName == username).first()
    # redis
    # if await request.app.state.redis.get(user.username) is None:
    #     raise HTTPException(detail='redis 数据失效', status_code=status.HTTP_408_REQUEST_TIMEOUT)
    if user is None:
        raise credentials_exception
    return user
