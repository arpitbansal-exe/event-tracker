#include <thread>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <windows.h>
#include <sysinfoapi.h>

#include "DeviceInfo.hpp"
#include "DeviceInfoFlags.hpp"
void DeviceInfo::collect(int flags) {
    info.clear();
    if (flags & PLATFORM)     info["platform"] = getPlatform();
    if (flags & ARCHITECTURE) info["architecture"] = getArchitecture();
    if (flags & HOSTNAME)     info["hostname"] = getHostName();
    if (flags & DEVICE_ID)    info["device_id"] = getDeviceID();
    if (flags & CPU_CORES)    info["cpu_cores"] = std::to_string(getCpuCores());
    if (flags & RAM_MB)       info["ram_mb"] = std::to_string(getRamMB());
}

std::string DeviceInfo::getPlatform() {
    return "Windows"; // You can later add cross-platform logic
}

std::string DeviceInfo::getArchitecture() {
#if defined(_M_X64) || defined(__x86_64__)
    return "x86_64";
#elif defined(_M_IX86) || defined(__i386__)
    return "x86";
#elif defined(__aarch64__)
    return "arm64";
#else
    return "unknown";
#endif
}

std::string DeviceInfo::getHostName() {
    char buffer[256];
    DWORD size = sizeof(buffer);
    if (GetComputerNameA(buffer, &size)) {
        return std::string(buffer);
    }
    return "unknown";
}

std::string DeviceInfo::getDeviceID() {
    // Save to local file if not present
    const std::string path = "Event_Tracker_device_id.txt";
    std::ifstream in(path);
    std::string id;
    if (in >> id) return id;

    // Generate UUID
    UUID uuid;
    UuidCreate(&uuid);
    RPC_CSTR str;
    UuidToStringA(&uuid, &str);
    id = reinterpret_cast<char*>(str);
    RpcStringFreeA(&str);

    std::ofstream out(path);
    out << id;
    return id;
}

int DeviceInfo::getCpuCores() {
    return std::thread::hardware_concurrency();
}

int DeviceInfo::getRamMB() {
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    if (GlobalMemoryStatusEx(&status)) {
        return static_cast<int>(status.ullTotalPhys / (1024 * 1024));
    }
    return -1;
}

const std::map<std::string, std::string>& DeviceInfo::getInfo() const {
    return info;
}