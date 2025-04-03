from typing import Union
import uvicorn
from fastapi import FastAPI

app = FastAPI()


@app.get("/")
def read_root():
    return {"Hello": "World"}


@app.post("/items/{item_id}", tags=["物品信息"])
def read_item(item_id: int, ):
    return {"item_id": item_id}


if __name__ == "__main__":
    uvicorn.run("main:app", port=8080, reload=True)