from fastapi import FastAPI
from .synchronizeData import synchronizedData_router


app_sysdata = FastAPI(
    title="同步数据接口",docs_url="/api/docs",openapi_url="/api"
)

app_sysdata.include_router(synchronizedData_router,prefix="/api")