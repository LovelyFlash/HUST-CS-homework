from fastapi import APIRouter
from .endpoints import (
    login_router, ec_router, file_router, stuInfo_router, failA_router,courseDim_router,
    classDim_router,gradeDim_router,user_router, majorDim_router, scoreDim_router, test_api
)

v1 = APIRouter(prefix="/v1")

v1.include_router(login_router, tags=['用户登陆'])
v1.include_router(user_router,tags=["用户管理"])
v1.include_router(ec_router, tags=["优良学风班"])
v1.include_router(file_router, tags=["文件操作"])
v1.include_router(stuInfo_router, tags=["学生信息"])
v1.include_router(failA_router,tags=['不及格分析'])
v1.include_router(courseDim_router,tags=['课程维度'])
v1.include_router(gradeDim_router,tags=['年级维度'])
v1.include_router(classDim_router,tags=['班级维度'])
v1.include_router(majorDim_router, tags=["专业维度"])
v1.include_router(scoreDim_router, tags=["分数维度"])

v1.include_router(test_api,tags=["测试API"])