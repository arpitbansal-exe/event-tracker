# 📊 EventTracker C++ SDK

A lightweight, extensible C++ library to collect, queue, and dispatch event telemetry from client applications to a remote HTTP endpoint.

---

## 🚀 Features

- ✅ **Asynchronous Event Tracking**  
  Events are queued and sent in the background via a worker thread — non-blocking to your main thread.

- 📦 **Built-in Device Info Collection**  
  Optionally collect platform, device ID, RAM, and more using flag-based configuration.

- 🌐 **Configurable Endpoint**  
  Easily initialize and switch environments (e.g., dev/staging/prod).

- 🧪 **Test Mode**  
  Print payloads locally without making HTTP requests — great for debugging and development.

- 🧵 **Safe Shutdown and Flush**  
  Ensures events in the queue are delivered before exiting.

---

## 🧩 API Overview

### ⚙️ Initialization

```cpp
EventTracker::init("https://your-api.com/events", "1.0.0");
```
### ⚙️ Global Fields 
These fields will be attached to every event.
```cpp
EventTracker::setGlobalFields({
    {"session_id", "abc-123"},
    {"env", "production"}
});

```

### 📱 Enable Device Info Collection
```cpp
EventTracker::enableDeviceInfo(DeviceInfoFlags::PLATFORM | DeviceInfoFlags::DEVICE_ID);
```
Choose what device data to attach using DeviceInfoFlags.
All Flags:


### 📝 Track an Event
Creates and queues an event.
```cpp
EventTracker::event("user_logged_in", {
    {"user_id", "u_001"},
    {"method", "google"}
});
```


### 🧪 Enable Test Mode
Disables actual network calls. Payloads will be printed to stdout.
```cpp
EventTracker::setTestMode(true);
```


### 🚰 Flush Pending Events
Force all events in the queue to be sent.
```cpp
EventTracker::flush();
```


### 🛑 Shutdown
Stops the queue worker and gracefully exits. Call this before application exit to avoid losing events.
```cpp
EventTracker::shutdown();
```



## 🛠️ Future Improvements
 - Retry Mechanism: Automatically retry failed network sends.

 - Batching: Send multiple events together in a single HTTP call.

 - Rate Limiting: Add throttling to avoid spamming endpoints.

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

