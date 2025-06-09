#include "Transporter.hpp"
#include <curl/curl.h>
#include <iostream>
#include "EventTracker.hpp"
#include <nlohmann/json.hpp>
#include "EventTrackerConfig.hpp"
using json = nlohmann::json;

bool Transporter::send(const std::vector<json>& events) {
    const std::string& server_endpoint = EventTracker::getServerEndPoint();
	QueueConfig queue_config = EventTracker::getQueueConfig();
    const std::string& auth_token = queue_config.authToken;
    if (server_endpoint.empty()) {
        std::cerr << "Error: Server endpoint is empty.\n";
        return false;
    }

    // Combine events into a single string
    std::string payload = createEventPayload(events);

    if (EventTracker::isTestMode()) {
        std::cout << "[TEST MODE] Batched Event Payload:\n" << payload << std::endl;
        return true;
    }

    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Error: Failed to initialize CURL.\n";
        return false;
    }

    curl_easy_setopt(curl, CURLOPT_URL, server_endpoint.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // Add the Authorization header
    std::string auth_header = "Authorization: Bearer ";
    auth_header += auth_token;
    headers = curl_slist_append(headers, auth_header.c_str());

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "CURL Error: " << curl_easy_strerror(res) << std::endl;
        return false;
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    return true;
}

std::string Transporter::createEventPayload(const std::vector<json>& events) {
    try {
        json payload = {
            {"events", events},
            {"device_info", EventTracker::getDeviceInfo()},
            {"client_version", EventTracker::getClientVersion()},
            {"event_lib_version", EVENT_TRACKER_VERSION},
            {"global_fields", EventTracker::getGlobalFields()}
        };

        return payload.dump();
    }
    catch (const json::exception& e) {
        // Log error and return empty JSON or throw
        // Logger::error("Failed to create event payload: {}", e.what());
        return "{}";
    }
}