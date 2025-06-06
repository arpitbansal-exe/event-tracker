# 📖 API Reference

This document describes the public interface and types exposed by the EventTracker SDK.

## 🔧 Initialization

```cpp
void EventTracker::init(const std::string& endpoint, const std::string& client_version, QueueConfig& config);
```

Initializes the SDK with server URL, version, and queue settings.

## 🌍 Global Fields

```cpp
void EventTracker::setGlobalFields(const std::map<std::string, std::string>& gfields);
```

Sets metadata to attach to every event.

## 📝 Event Tracking

```cpp
void EventTracker::event(const std::string& eventName, const std::map<std::string, std::string>& data);
```

Creates and queues a custom event with name and key-value pairs.

## 📱 Device Info

```cpp
void EventTracker::enableDeviceInfo(int flags);
```

Enables platform and hardware metadata collection.

```cpp
const std::map<std::string, std::string>& EventTracker::getDeviceInfo();
```

Returns collected device information.

## 🧪 Test Mode

```cpp
void EventTracker::setTestMode(bool enabled);
```

If `true`, skips HTTP sending and prints event payloads to stdout.

```cpp
bool EventTracker::isTestMode();
```

Checks if test mode is currently enabled.

## 🚰 Flush Events

```cpp
void EventTracker::flush();
```

Forces immediate sending of all queued events.

## 🛑 Shutdown

```cpp
void EventTracker::shutdown();
```

Safely stops the worker thread and flushes any remaining events.
