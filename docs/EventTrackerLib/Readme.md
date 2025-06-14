# 📊 EventTracker SDK Overview

## What is EventTracker?

**EventTracker** is a lightweight, extensible C++ SDK designed to collect, queue, and dispatch telemetry and event data from client applications to a remote HTTP endpoint. It is designed with performance, ease-of-use, and flexibility in mind.

## 🎯 Goals

- **Minimal Integration Friction**: Easy to integrate into existing C++ projects.
- **Asynchronous and Non-blocking**: All event tracking is done off the main thread.
- **Extensible**: Add custom fields, events, or transports as needed.
- **Cross-Platform Readiness**: Built with compatibility for Windows, Linux, and macOS in mind.

## ✨ Key Features

- ✅ **Asynchronous Event Queueing** using a dedicated worker thread
- 🧪 **Test Mode** for debugging event payloads without sending HTTP requests
- 🧵 **Safe Shutdown and Flushing** before app termination
- 📦 **Queue Configuration**: Custom batch sizes, retry logic, queue length, etc.
- 📱 **Device Info** collection via flag-based configuration
- 🔌 **Pluggable Transport Layer** to support alternate delivery mechanisms

## 💡 Design Principles

- **Thread Safety**: Internally uses mutexes and condition variables.
- **Modular**: Core functionalities like event building, queueing, and transport are separate.
- **Minimal Dependencies**: Uses libcurl and nlohmann/json.
- **High Performance**: Non-blocking event handling, minimal overhead.

## 🔧 Components

| Component | Responsibility |
|-----------|----------------|
| `EventTracker` | Public API for initializing and logging events |
| `EventQueue` | Manages async queuing, batching, retrying |
| `Transporter` | Sends batched events over HTTP |
| `EventBuilder` | Serializes events and global/device data into JSON |
| `DeviceInfo` | Gathers runtime system information |

## 🔍 Who Should Use This?

- Developers of native applications who need telemetry
- Internal tooling that requires analytics

## 📈 Example Use Cases

- Track user logins, screen views, job completions
- Log debug or error information
- Collect performance or usage metrics

## Documentation
- [Configuration](./configuration.md)
- [API Reference](./api_reference.md)
- [HTTP Payload Structure](./http_payload.md)