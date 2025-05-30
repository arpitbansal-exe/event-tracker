#pragma once
#include <string>
#include <map>
#pragma comment(lib, "Rpcrt4.lib")
class DeviceInfo {
public:
    void collect(int flags);
    const std::map<std::string, std::string>& getInfo() const;

private:
    std::map<std::string, std::string> info;

private:
    std::string getPlatform();
    std::string getArchitecture();
    std::string getHostName();
    std::string getDeviceID();       // e.g., saved UUID per machine
    int getCpuCores();
    int getRamMB();
};