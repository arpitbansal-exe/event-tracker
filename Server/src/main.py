import uuid
import json
from fastapi import FastAPI, Request, HTTPException, Depends

import asyncio
from src.redis_consumer import flush_events_from_redis

from src.models import EventBatch
from src.auth import verify_token
from src.utils.logger import get_logger
from src.db import init_db
from contextlib import asynccontextmanager
from src.redis_client import init_redis
from src.redis_client import get_redis_pool

@asynccontextmanager
async def lifespan(app: FastAPI):
    logger.info("📦 Starting up... initializing database")
    await init_db()
    await init_redis()

    asyncio.create_task(flush_events_from_redis())

    yield
    logger.info("🧹 Shutting down...")
app = FastAPI(title="EventTracker Ingestion Service", lifespan=lifespan)

logger = get_logger()


@app.post("/test")
async def ingest_events(payload: EventBatch, _auth: None = Depends(verify_token)):
    redis_pool = get_redis_pool()  # 🔄 Get Redis pool
    try:
        for event in payload.events:
            event_data = {
                "id": str(uuid.uuid4()),
                "event_name": event.event_name,
                "timestamp": event.timestamp,
                "data": event.data,
                "client_version": payload.client_version,
                "event_lib_version": payload.event_lib_version,
                "global_fields": payload.global_fields,
                "device_info": payload.device_info
            }
            await redis_pool.rpush("event_queue", json.dumps(event_data, default=str))   #push to redis list
    
        return {"status": "ok", "queued": len(payload.events)}
    except Exception as e:
        logger.warning(f"Error Pushing the event to reqis queue: {e}")
        return {"status": 500, "msg": "Internal Server Error"}

@app.middleware("http")
async def log_requests(request: Request, call_next):
    try:
        body = await request.body()
        logger.debug(f"Raw Request: {body.decode('utf-8')}")
    except Exception as e:
        logger.warning(f"Could not decode request body: {e}")
    return await call_next(request)