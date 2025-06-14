# ⚙️ Configuration Guide
  - [QueueConfig](#queueconfig-structure)
  - [DeviceInfoFlags](#-deviceinfoflags)

## QueueConfig Structure

Used to control how the event queue behaves:

```cpp
enum class DropPolicy {
    DROP_OLDEST,
    DROP_NEWEST
};

struct QueueConfig {
    size_t maxQueueSize = 100;          // Max events in queue
    size_t batchSize = 10;              // Events per HTTP POST
    size_t maxRetries = 3;              // Max retry attempts
    size_t retryDelayMs = 2000;         // Delay between retries
    DropPolicy dropPolicy = DropPolicy::DROP_OLDEST;
};
```

## 🎛️ Configuration Parameters

### Queue Management

- **`maxQueueSize`** (default: 100)
  - Maximum number of events stored in memory before dropping occurs
  - Prevents unbounded memory growth in high-volume scenarios
  - When limit is reached, events are dropped according to the `dropPolicy`

- **`dropPolicy`** (default: `DROP_OLDEST`)
  - **`DROP_OLDEST`**: Remove the oldest events when queue is full
  - **`DROP_NEWEST`**: Discard incoming events when queue is full
  - Helps maintain memory bounds while preserving most relevant data

### Batching Behavior

- **`batchSize`** (default: 10)
  - Number of events bundled together in a single HTTP request
  - Larger batches reduce network overhead but increase memory usage
  - Smaller batches provide faster event delivery with more frequent requests

### Retry Logic

- **`maxRetries`** (default: 3)
  - Maximum number of retry attempts for failed HTTP requests
  - Set to 0 to disable retries entirely
  - Higher values improve reliability but may delay event processing

- **`retryDelayMs`** (default: 2000ms)
  - Milliseconds to wait between retry attempts
  - Exponential backoff is not implemented - uses fixed delay
  - Helps prevent overwhelming a struggling server

## ⚠️ Important Considerations

- **Memory Usage**: `maxQueueSize × average_event_size` determines peak memory consumption
- **Network Efficiency**: Larger `batchSize` reduces HTTP overhead but increases latency
- **Retry Behavior**: High retry counts can cause significant delays during network issues
- **Drop Policy**: Choose based on whether recent or historical events are more important


### Example for Reliable Delivery
```cpp
QueueConfig reliable;
reliable.maxQueueSize = 200;
reliable.batchSize = 15;
reliable.maxRetries = 5;
reliable.retryDelayMs = 3000;
reliable.dropPolicy = DropPolicy::DROP_OLDEST;
```




## 🏁 DeviceInfoFlags

Control which device details to collect and attach to every event:

```cpp
enum DeviceInfoFlags {
    NONE = 0,
    PLATFORM = 1 << 0,
    ARCHITECTURE = 1 << 1,
    RAM = 1 << 2,
    HOSTNAME = 1 << 3,
    CPU_CORES = 1 << 4,
    DEVICE_ID = 1 << 5,
    ALL = PLATFORM | ARCHITECTURE | RAM | HOSTNAME | CPU_CORES | DEVICE_ID
};
```

## 🎯 Flag Descriptions

| Flag | Description | Example Value |
|------|-------------|---------------|
| `NONE` | No device information collected | - |
| `PLATFORM` | Operating system name | "Windows", "Linux", "macOS" |
| `ARCHITECTURE` | CPU architecture | "x86_64", "arm64", "i386" |
| `RAM` | Total system memory in MB | "8192", "16384" |
| `HOSTNAME` | Computer/device name | "DESKTOP-ABC123", "MacBook-Pro" |
| `CPU_CORES` | Number of CPU cores | "4", "8", "16" |
| `DEVICE_ID` | Unique device identifier | "90e02037-2192-4d33-9993-e8c7677b7f06" |
| `ALL` | All available device information | Combination of all flags |

## 💡 Usage Examples

### Minimal Information
```cpp
EventTracker::enableDeviceInfo(DeviceInfoFlags::PLATFORM | DeviceInfoFlags::ARCHITECTURE);
```

### Privacy-Conscious Setup
```cpp
EventTracker::enableDeviceInfo(DeviceInfoFlags::PLATFORM | DeviceInfoFlags::CPU_CORES);
```

### Full Telemetry
```cpp
EventTracker::enableDeviceInfo(DeviceInfoFlags::ALL);
```

### Disable All Device Info
```cpp
EventTracker::enableDeviceInfo(DeviceInfoFlags::NONE);
```

## 🎛 Recommended Defaults

## 🔒 Privacy Considerations

- **`HOSTNAME`**: May contain personally identifiable information
- **`DEVICE_ID`**: Creates a persistent unique identifier across sessions
- **`RAM`**: Generally safe but can contribute to device fingerprinting
- **`PLATFORM`** and **`ARCHITECTURE`**: Usually safe for analytics purposes

## ⚙️ Implementation Notes

- Flags use bitwise operations for efficient combination
- Device information is collected once at initialization
- All values are stored as strings in the final JSON payload
- Missing or unavailable information results in empty strings