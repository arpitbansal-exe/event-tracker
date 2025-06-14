# 📡 EventTracker Server

This server ingests telemetry or event data (e.g., from a C++ SDK), buffers it in **Redis**, and periodically flushes it in batches to a **PostgreSQL** (TimescaleDB) database. It's built using **FastAPI**, **asyncpg**, and **aioredis** for performance and scalability.

## 🚀 Features

- Accepts batched event data over HTTP POST
- Validates request schema using Pydantic models
- Buffers events in Redis (`event_queue` list)
- Background task periodically flushes events to PostgreSQL in batches
- Handles invalid events gracefully and logs warnings
- Uses `executemany()` for efficient DB inserts
- Handles UTC timestamps and ISO 8601 parsing

## 📦 Tech Stack

| Layer | Technology |
|-------|------------|
| API Server | FastAPI |
| Queue | Redis (via `aioredis`) |
| Database | PostgreSQL (with TimescaleDB) |
| ORM | asyncpg |
| Logging | Python logging module |
| Background | `asyncio` workers |

## 🔌 API Endpoint

### `POST /test`
Ingests batched telemetry events.

## 🔄 Redis Queue Structure

- **Key**: `event_queue`
- **Type**: Redis List (`LPUSH` / `LPOP`)
- **Value**: JSON stringified event object

## 🔁 Flush Worker

The background task:
- Runs every 5 seconds
- Pops up to 100 events per interval from Redis
- Parses and validates each event
- Uses `executemany()` to insert all valid events in a single DB transaction

## 🧪 Development & Testing

### Install dependencies
```bash
pip install -r requirements.txt
```

### Run server
```bash
cd server
uvicorn src.main:app --reload
```

### Run Redis and Postgres via Docker
```bash
docker-compose up -d redis postgres
```

## 🧪 Deployment
```bash
    docker-compose up --build
```

## 🏗️ Architecture Deep Dive

### Request Flow
1. **Client Request**: C++ SDK or any HTTP client sends POST request to `/test`
2. **Authentication**: API validates token from `Authorization` header
3. **Schema Validation**: Pydantic models validate incoming JSON payload
4. **Queue Buffering**: Valid events are pushed to Redis `event_queue` list
5. **Background Processing**: Worker thread pops events and flushes to TimescaleDB
6. **Response**: Client receives immediate HTTP 200 response