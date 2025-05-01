from typing import Union, Optional
import uvicorn
from fastapi import FastAPI
from fastapi import APIRouter

func2 = APIRouter()

@func2.post("/usr_id")
async def search_usr_id(usr_id: Optional[str] = None):
    return {"usr_id": usr_id}