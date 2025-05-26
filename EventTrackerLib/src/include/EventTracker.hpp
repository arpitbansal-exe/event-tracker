#pragma once

#include <string>
#include <map>


class EventTracker {
public:
    static void init(const std::string& server_endpoint, const std::string& client_version);
    static void setGlobalFields(const std::map<std::string, std::string>& gfields);
    static void event(const std::string& eventName, const std::map<std::string, std::string>& data);

private:
    static std::string _server_endpoint;
    static std::string _client_version;
    static std::map<std::string, std::string> _client_globalFields;
};
