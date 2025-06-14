# src/db.py
import asyncpg
import os
import asyncio
from src.utils.logger import get_logger

logger = get_logger()

db_pool = None

async def init_db():
    global db_pool
    retries = 5
    delay = 2  # seconds

    for attempt in range(1, retries + 1):
        try:
            db_pool = await asyncpg.create_pool(
                user=os.getenv("POSTGRES_USER"),
                password=os.getenv("POSTGRES_PASSWORD"),
                database=os.getenv("POSTGRES_DB"),
                host=os.getenv("POSTGRES_HOST"),
                port=5432
            )

            async with db_pool.acquire() as conn:
                await conn.execute("""
                    CREATE TABLE IF NOT EXISTS events (
                        id SERIAL,
                        event_name TEXT,
                        timestamp TIMESTAMPTZ NOT NULL,
                        data JSONB,
                        client_version TEXT,
                        event_lib_version TEXT,
                        global_fields JSONB,
                        device_info JSONB,
                        PRIMARY KEY (id, timestamp)
                    );
                    SELECT create_hypertable('events', 'timestamp', if_not_exists => TRUE);
                """)

            logger.info("✅ Database initialized successfully.")
            return

        except Exception as e:
            logger.error(f"❌ Attempt {attempt}/{retries} - DB init failed: {e}")
            if attempt == retries:
                raise
            await asyncio.sleep(delay)

def get_db_pool():
    if db_pool is None:
        raise RuntimeError("Database pool not initialized")
    return db_pool
