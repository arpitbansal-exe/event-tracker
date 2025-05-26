#include "EventTracker.hpp"
#include "EventBuilder.hpp"
#include "Transporter.hpp"

#include <chrono>
// DEFINITIONS of static members
std::string EventTracker::_server_endpoint = "";
std::string EventTracker::_client_version = "";
std::map<std::string, std::string> EventTracker::_client_globalFields = {};

void EventTracker::init(const std::string& server_endpoint, const std::string& client_version) {
    _server_endpoint = server_endpoint;
    _client_version = client_version;

#ifdef DEBUG
    std::cout << "Event Tracker Init"<<std::endl;
    std::cout << "Server Endpoint: "<< _server_endpoint <<std::endl;
    std::cout << "Client Version: " << _client_version  << std::endl;
#endif // 

}

void EventTracker::setGlobalFields(const std::map<std::string, std::string>& gfields) {
    _client_globalFields = gfields;
#ifdef DEBUG
    std::cout << "Global fields set" << std::endl;
#endif // 
}

void EventTracker::event(const std::string& eventName, const std::map<std::string, std::string>& data) {
    auto fullPayload = EventBuilder::build(eventName, _client_version, _client_globalFields, data);
    Transporter::send(_server_endpoint, fullPayload);
}
