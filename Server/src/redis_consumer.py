import json
import asyncio
from datetime import datetime
from dateutil.parser import isoparse
from src.db import get_db_pool
from src.redis_client import get_redis_pool
from src.utils.logger import get_logger

logger = get_logger()

async def flush_events_from_redis(batch_size: int = 100, interval: int = 5):
    redis = get_redis_pool()
    db = get_db_pool()

    while True:
        try:
            events = []
            for _ in range(batch_size):
                raw = await redis.lpop("event_queue")
                if raw is None:
                    break
                events.append(json.loads(raw))

            if events:
                values = []
                for event in events:
                    try:
                        timestamp_raw = event["timestamp"]
                        # Ensure we convert string to datetime
                        timestamp = (
                            isoparse(timestamp_raw)
                            if isinstance(timestamp_raw, str)
                            else timestamp_raw
                        )
                        values.append((
                            event["event_name"],
                            timestamp,
                            json.dumps(event["data"], default=str),
                            event["client_version"],
                            event["event_lib_version"],
                            json.dumps(event["global_fields"], default=str),
                            json.dumps(event["device_info"], default=str)
                        ))
                    except Exception as e:
                        logger.warning(f"⚠️ Skipping invalid event: {e}, Event: {event}")

                if values:
                    async with db.acquire() as conn:
                        async with conn.transaction():
                            await conn.executemany("""
                                INSERT INTO events (
                                    event_name, timestamp, data, client_version,
                                    event_lib_version, global_fields, device_info
                                ) VALUES ($1, $2, $3, $4, $5, $6, $7)
                            """, values)

                    logger.info(f"✅ Flushed {len(values)} events to DB (batch)")

        except Exception as e:
            logger.error(f"🚨 Redis flush failed: {e}")

        await asyncio.sleep(interval)