from typing import Union
import uvicorn
from fastapi import FastAPI
from fastapi import APIRouter

func1 = Router()

@func1.get("/usr_id/{usr_id}")
def get_usr_id(usr_id: Union[int, None] = None):
    return {"usr_id": usr_id}