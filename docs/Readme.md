# 📊 EventTracker C++ SDK

**EventTracker** is a lightweight, extensible C++ SDK designed to collect, queue, and dispatch telemetry and event data from client applications to a remote HTTP endpoint. It is designed with performance, ease-of-use, and flexibility in mind.

**EventTracker**
## ✨ Key Features

- ✅ **Asynchronous Event Queueing** using a dedicated worker thread
- 🧪 **Test Mode** for debugging event payloads without sending HTTP requests
- 🧵 **Safe Shutdown and Flushing** before app termination
- 📦 **Queue Configuration**: Custom batch sizes, retry logic, queue length, etc.
- 📱 **Device Info** collection via flag-based configuration
- 🔌 **Pluggable Transport Layer** to support alternate delivery mechanisms

---

## 🧩 API Overview

### ⚙️ Initialization

```cpp
EventTracker::init("https://your-api.com/events", "1.0.0");
```
### 📝 Track an Event
Creates and queues an event.
```cpp
EventTracker::event("user_logged_in", {
    {"user_id", "u_001"},
    {"method", "google"}
});
```
Please refer [Event Tracker Docs ](docs/EventTrackerLib) for detailed explaination.


# 🚀 Server Infrastructure

**EventTracker Server** is a high-performance event ingestion and processing system built with modern Python technologies, designed to handle high-volume telemetry data from multiple client applications.

## 🏗️ Server Architecture

1. **API Layer**: FastAPI receives HTTP POST requests with batched events
2. **Queue Layer**: Events are buffered in Redis for reliable processing
3. **Worker Layer**: Background tasks flush events to database in batches
4. **Storage Layer**: TimescaleDB stores time-series event data efficiently
5. **Analytics Layer**: Grafana provides real-time monitoring and insights

## 📦 Server Tech Stack

| Component | Technology |
|-----------|------------|
| API Server | FastAPI + uvicorn |
| Message Queue | Redis |
| Database | PostgreSQL + TimescaleDB |
| Analytics | Grafana |
| Deployment | Docker Compose |

Please refer [Server Docs ](docs/Server) for detailed explaination.

