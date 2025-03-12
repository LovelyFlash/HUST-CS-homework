from fastapi import FastAPI

from core.config import config
from .v1 import v1

app = FastAPI(
    title=config.PROJECT_NAME,docs_url="/apis/docs",openapi_url="/api"
)

app.include_router(v1,prefix="/apis")