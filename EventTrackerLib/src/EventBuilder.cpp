#include "EventBuilder.hpp"
//#include <nlohmann/json.hpp>
#include "EventTrackerConfig.hpp"
#include <chrono>
#include <ctime>
#include <sstream>
#include "EventTracker.hpp"
//using json = nlohmann::json;

std::string EventBuilder::build(
    const std::string& eventName,
    const std::string& version,
    const std::map<std::string, std::string>& globals,
    const std::map<std::string, std::string>& data
) {
#if 0
    //json payload;
    //payload["event_name"] = eventName;
    //payload["version"] = version;

    //// Timestamp
    //auto now = std::chrono::system_clock::now();
    //auto time_t_now = std::chrono::system_clock::to_time_t(now);
    //payload["timestamp"] = std::ctime(&time_t_now);

    //payload["global_fields"] = globals;
    //payload["data"] = data;
    return "Payload";
    //return payload.dump(); // JSON string
#else
    std::ostringstream oss;

    // Event metadata
    oss << "event_name=" << eventName << ";";
    oss << "version=" << version << ";";

    // Timestamp (ISO format)
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm tm_struct;
#ifdef _WIN32
    localtime_s(&tm_struct, &now_time);
#else
    localtime_r(&now_time, &tm_struct);
#endif
    char buffer[32];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%S", &tm_struct);
    oss << "timestamp=" << buffer << ";";

    // Global fields
    for (const auto& [key, value] : globals) {
        oss << "global_" << key << "=" << value << ";";
    }

    // Event data
    for (const auto& [key, value] : data) {
        oss << key << "=" << value << ";";
    }

    //Device Data
    auto deviceInfo = EventTracker::getDeviceInfo();
    for (const auto& [key, value] : deviceInfo) {
        oss << key << "=" << value << ";";
    }
    std::string result = oss.str();

    // Remove trailing semicolon
    if (!result.empty() && result.back() == ';') {
        result.pop_back();
    }

    return result;
#endif // 0
}
