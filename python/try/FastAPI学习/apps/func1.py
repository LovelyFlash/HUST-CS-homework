from typing import Union, Optional
import uvicorn
from fastapi import FastAPI
from fastapi import APIRouter

func1 = APIRouter()

@func1.get("/usr_id")
async def get_usr_id(usr_id: Optional[str] = None):
    return {"usr_id": usr_id}