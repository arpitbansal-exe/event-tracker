# 📊 EventTracker C++ SDK

**EventTracker** is a lightweight, extensible C++ SDK designed to collect, queue, and dispatch telemetry and event data from client applications to a remote HTTP endpoint. It is designed with performance, ease-of-use, and flexibility in mind.


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

Please refer [docs](docs/overview.md) for detailed explaination.


## 🛠️ Future Improvements
 - Persistent Queue: Save events to disk and restore after crashes.

 - Cross-platform Support: Linux/macOS/Windows full support matrix.

## 🧪 Dependencies
- libcurl for HTTP requests
- C++17 or later
- Windows SDK (for UuidCreate, etc., if used on Windows)


## 📄 License
- Open to use by anyone.
- Feedback is appreciated
- Credits must be given if used. 
  -- Arpit Bansal (arpitbansal.exe@gmail.com)

