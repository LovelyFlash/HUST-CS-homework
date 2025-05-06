import os

import aioredis
from aioredis import Redis

from core.config import config

async def sys_cache() -> Redis:
    """
    系统缓存
    :return:返回redis 连接池
    """
    sys_cache_pool = aioredis.ConnectionPool.from_url(
        f"redis://{os.getenv('CACHE_HOST',config.REDIS_HOST)}:{os.getenv('CACHE_PORT',config.REDIS_PORT)}",
        db=os.getenv('CACHE_DB',1), # redis中有16个数据库，这里使用 1
        encoding='utf-8',
        decode_responses=True
    )
    return Redis(connection_pool=sys_cache_pool)

async def course_cache() -> Redis:
    """
    课程缓存
    :return: cache 连接池
    """
    # 从URL方式创建redis连接池
    print(f"redis://{config.REDIS_PASSWORD}@{os.getenv('CACHE_HOST',config.REDIS_HOST)}:{os.getenv('CACHE_PORT',config.REDIS_PORT)}")
    course_cache_pool = aioredis.ConnectionPool.from_url(
        # "redis://:password@host:6379/0?encoding=utf-8"
        f"redis://:{config.REDIS_PASSWORD}@{os.getenv('CACHE_HOST',config.REDIS_HOST)}:{os.getenv('CACHE_PORT',config.REDIS_PORT)}",
        db=os.getenv('CACHE_DB',2), # redis中有16个数据库，这里使用 2
        encoding='utf-8',
        decode_responses=True
    )
    return Redis(connection_pool=course_cache_pool)

async def stuInfo_cache() -> Redis:
    """
    课程缓存
    :return: cache 连接池
    """
    # 从URL方式创建redis连接池
    print(f"redis://{config.REDIS_PASSWORD}@{os.getenv('CACHE_HOST',config.REDIS_HOST)}:{os.getenv('CACHE_PORT',config.REDIS_PORT)}")
    stuInfo_cache_pool = aioredis.ConnectionPool.from_url(
        # "redis://:password@host:6379/0?encoding=utf-8"
        f"redis://:{config.REDIS_PASSWORD}@{os.getenv('CACHE_HOST',config.REDIS_HOST)}:{os.getenv('CACHE_PORT',config.REDIS_PORT)}",
        db=os.getenv('CACHE_DB',3), # redis中有16个数据库，这里使用 3
        encoding='utf-8',
        decode_responses=True
    )
    return Redis(connection_pool=stuInfo_cache_pool)

if __name__ == '__main__':
    pass
