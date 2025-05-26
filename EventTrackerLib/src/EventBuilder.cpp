#include "EventBuilder.hpp"
//#include <nlohmann/json.hpp>
#include "EventTrackerConfig.hpp"
#include <chrono>
#include <ctime>

//using json = nlohmann::json;

std::string EventBuilder::build(
    const std::string& eventName,
    const std::string& version,
    const std::map<std::string, std::string>& globals,
    const std::map<std::string, std::string>& data
) {
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
}
