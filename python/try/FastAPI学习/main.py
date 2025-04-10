from typing import Union
import uvicorn
from fastapi import FastAPI
from apps.func1 import func1

app= FastAPI()
app.include_router(func1, tags=["01 路径参数"])


if __name__ == "__main__":
    uvicorn.run("main:app", port=8080, reload=True)