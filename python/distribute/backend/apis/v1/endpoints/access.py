from datetime import timedelta


from fastapi import APIRouter,Depends,HTTPException,status
from fastapi.security import OAuth2PasswordRequestForm
from fastapi.requests import Request

from models import User
from core import verify_password,create_access_token
from core.auth import authenticate_user,sign_up_new_user,authenticate_user_cID
from core import deps
from schemas import UserCreate,Response400,Response200,ResponseToken
import schemas
from database.curd_ec import ec_get_by_grade
from database.session import get_db
from core import config,security

access_router = APIRouter()

