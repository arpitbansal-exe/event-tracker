#include "EventBuilder.hpp"
#include "EventTrackerConfig.hpp"
#include <chrono>
#include <ctime>
#include <sstream>
#include <iostream>
#include "EventTracker.hpp"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

json EventBuilder::build(
    const std::string& eventName,
    const std::map<std::string, std::string>& data
) {
    json payload;

    // Event metadata
    payload["event_name"] = eventName;

    // Timestamp in ISO 8601 format
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
    payload["timestamp"] = buffer;

    // Event data as nested object
    if (!data.empty()) {
        json event_data;
        for (const auto& [key, value] : data) {
            event_data[key] = value;
        }
        payload["data"] = event_data;
    }
    // Return compact JSON string (no pretty printing for actual payload)
    return payload;
}
