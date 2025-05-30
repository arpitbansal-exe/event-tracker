#pragma once

#include <string>
#include <map>

#include "DeviceInfo.hpp"
#include "DeviceInfoFlags.hpp"
#include "EventQueue.hpp"
#define DEBUG 1

class EventTracker {
public:
    //Init and Global Settings
    static void init(const std::string& server_endpoint, const std::string& client_version);
    static void setGlobalFields(const std::map<std::string, std::string>& gfields);
    
    //Event
    static void event(const std::string& eventName, const std::map<std::string, std::string>& data);
    
    //Device Info
    static void enableDeviceInfo(int flags);
    static const std::map<std::string, std::string>& getDeviceInfo();
    
    //Test Mode
    static void setTestMode(bool enabled);
    static bool isTestMode();

    //Event Queue Functions
    static void flush();
    static void shutdown();

    static std::string getServerEndPoint();
private:
    static std::string _server_endpoint;
    static std::string _client_version;
    static std::map<std::string, std::string> _client_globalFields;

    //device fields
    static inline int _deviceInfoFlags = DeviceInfoFlags::NONE;
    static inline DeviceInfo _deviceInfo;

    //test mode
    static bool _testMode;

    //Event Queue
    static inline std::unique_ptr<EventQueue> _queue;
};

