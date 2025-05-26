#pragma once

#include <string>
#include <map>

class EventBuilder {
public:
    static std::string build(
        const std::string& eventName,
        const std::string& version,
        const std::map<std::string, std::string>& globals,
        const std::map<std::string, std::string>& data
    );
};