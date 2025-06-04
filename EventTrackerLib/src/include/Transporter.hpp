#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Transporter {
public:
    static bool send(const std::vector<json>& events);
    static std::string createEventPayload(const std::vector<json>& events);
};