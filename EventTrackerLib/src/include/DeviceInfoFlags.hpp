#pragma once
enum DeviceInfoFlags {
    NONE = 0,
    PLATFORM = 1 << 0,
    ARCHITECTURE = 1 << 1,
    HOSTNAME = 1 << 2,
    DEVICE_ID = 1 << 3,
    CPU_CORES = 1 << 4,
    RAM_MB = 1 << 5,
    ALL_INFO = PLATFORM | ARCHITECTURE | HOSTNAME | DEVICE_ID | CPU_CORES | RAM_MB
};
