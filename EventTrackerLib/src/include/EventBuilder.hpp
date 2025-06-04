#pragma once

#include <string>
#include <map>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class EventBuilder {
public:
    static json build(
        const std::string& eventName,
        const std::map<std::string, std::string>& data
    );
};