#include "EventTracker.hpp"
#include "EventBuilder.hpp"
#include "Transporter.hpp"
#include "iostream"
#include <chrono>

// DEFINITIONS of static members
std::string EventTracker::_server_endpoint = "";
std::string EventTracker::_client_version = "";
std::map<std::string, std::string> EventTracker::_client_globalFields = {};
bool EventTracker::_testMode = false; 


void EventTracker::init(const std::string& server_endpoint, const std::string& client_version, QueueConfig& config) {
    _server_endpoint = server_endpoint;
    _client_version = client_version;

    _queue = std::make_unique<EventQueue>(&Transporter::send, config);

#ifdef DEBUG
    std::cout << "Event Tracker Init"<<std::endl;
    std::cout << "Server Endpoint: "<< _server_endpoint <<std::endl;
    std::cout << "Client Version: " << _client_version  << std::endl;
#endif // 

}

void EventTracker::setGlobalFields(const std::map<std::string, std::string>& gfields) {
    _client_globalFields = gfields;
#ifdef DEBUG
    std::cout << "Global fields" << std::endl;
    for (const auto& gfield : _client_globalFields) {
        std::cout << gfield.first << " : " << gfield.second << std::endl;
    }
#endif // 
}

void EventTracker::event(const std::string& eventName, const std::map<std::string, std::string>& data) {
    auto fullPayload = EventBuilder::build(eventName, _client_version, _client_globalFields, data);
    if (_testMode) {
        std::cout << "[TEST MODE] Event payload:\n" << fullPayload << std::endl;
        return;
    }
    else {
        _queue->push(fullPayload);
    }
}

void EventTracker::enableDeviceInfo(int flags) {
    _deviceInfoFlags = flags;
    _deviceInfo.collect(flags);
}

const std::map<std::string, std::string>& EventTracker::getDeviceInfo() {
    return _deviceInfo.getInfo();
}

void EventTracker::setTestMode(bool enabled) {
    _testMode = enabled;
}

bool EventTracker::isTestMode() {
    return _testMode;
}


void EventTracker::flush() {
    if (_queue) _queue->flush();
}

void EventTracker::shutdown() {
    if (_queue) _queue->shutdown();
}

std::string EventTracker::getServerEndPoint() {
    return _server_endpoint;
}