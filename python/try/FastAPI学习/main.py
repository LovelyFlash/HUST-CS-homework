from typing import Union
import uvicorn
from fastapi import FastAPI
from fun1 import app1

app


if __name__ == "__main__":
    uvicorn.run("main:app", port=8080, reload=True)