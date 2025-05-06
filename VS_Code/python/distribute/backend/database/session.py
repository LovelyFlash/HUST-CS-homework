from sqlalchemy import create_engine
import sqlalchemy
from asyncio import current_task
from sqlalchemy.orm import sessionmaker,scoped_session
# from sqlalchemy.ext.asyncio import create_async_engine,AsyncSession
from sqlalchemy import create_engine

from core.config import config
import logging

engine = create_engine(
    config.SQLALCHEMY_DATABASE_URI
)

# async_engine = create_async_engine(
#     config.SQLALCHEMY_DATABASE_URI_async,future=True,echo=True
# )
SessionLocal = sessionmaker(autocommit=False,autoflush=False,bind=engine)

# SessionLocal_async = scoped_session(
#     sessionmaker(autocommit=False,autoflush=False,bind=async_engine,class_=AsyncSession),scopefunc=current_task)

def get_db():
    logging.getLogger('sqlalchemy.engine').setLevel(logging.WARNING)
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()

# async def get_db_async():
#     db =  SessionLocal_async()
#     try:
#         yield db
#     finally:
#         db.close()