from fastapi import APIRouter, FastAPI

# Define the router
func4 = APIRouter()

@func4.post("/form/")
async def create_item(name: str, description: str | None = None, price: float = 0.0, tax: float | None = None):
    total_price = price + (tax if tax else 0)
    return {
        "name": name,
        "description": description,
        "price": price,
        "tax": tax,
        "total_price": total_price,
    }