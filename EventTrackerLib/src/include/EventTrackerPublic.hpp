#pragma once
#include <string>
#include <map>
#include "EventTrackerConfig.hpp"
#include "DeviceInfoFlags.hpp"


class EventTracker {
public:
    static void init(const std::string& server_endpoint, const std::string& client_version, QueueConfig& config);
    static void setGlobalFields(const std::map<std::string, std::string>& gfields);
    static void event(const std::string& eventName, const std::map<std::string, std::string>& data);
    static void enableDeviceInfo(int flags);
    static const std::map<std::string, std::string>& getDeviceInfo();
    static void setTestMode(bool enabled);
    static bool isTestMode();
    static void flush();
    static void shutdown();
    static std::string getServerEndPoint();

private:
    // Hide all implementation details - no JSON types visible
    static std::string _server_endpoint;
    static std::string _client_version;
    static std::map<std::string, std::string> _client_globalFields;
    static bool _testMode;
    static int _deviceInfoFlags;

    // Forward declare or use void* for internal members
    static void* _queue;  // Will be cast to EventQueue* internally
};