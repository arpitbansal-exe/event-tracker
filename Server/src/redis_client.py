import os
import redis.asyncio as redis

redis_pool = None

async def init_redis():
    global redis_pool
    redis_pool = redis.Redis(
        host=os.getenv("REDIS_HOST", "redis"),
        port=int(os.getenv("REDIS_PORT", 6379)),
        decode_responses=True
    )

def get_redis_pool():
    if redis_pool is None:
        raise RuntimeError("Database pool not initialized")
    return redis_pool