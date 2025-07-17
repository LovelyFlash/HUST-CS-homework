from fastapi import APIRouter
from pydantic import BaseModel

# 定义 Pydantic 模型
class Item(BaseModel):
    name: str
    description: str | None = None  # 可选字段
    price: float
    tax: float | None = None  # 可选字段

# Define the router
func3 = APIRouter()

@func3.post("/items/")
async def create_item(item: Item):
    """
    接收请求体数据并返回处理结果
    """
    total_price = item.price + (item.tax if item.tax else 0)
    return {
        "name": item.name,
        "description": item.description,
        "price": item.price,
        "tax": item.tax,
        "total_price": total_price,
    }