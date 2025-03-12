from starlette.requests import Request
import uvicorn
import logging


logging.basicConfig()
logging.getLogger('sqlalchemy.engine').setLevel(logging.INFO)
from sysData import app_sysdata


if __name__ == '__main__':
    uvicorn.run("main_sysdata:app_sysdata",host="127.0.0.1",debug=True,reload=True,port=8889)
