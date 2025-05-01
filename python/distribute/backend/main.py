from fastapi import FastAPI,Depends
from starlette.requests import Request
import uvicorn
import logging


logging.basicConfig()
logging.getLogger('sqlalchemy.engine').setLevel(logging.INFO)
from apis import app


if __name__ == '__main__':
    uvicorn.run("main:app",host="127.0.0.1",debug=True,reload=True,port=8888)

