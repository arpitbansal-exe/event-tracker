#include "Transporter.hpp"
#include <curl/curl.h>
#include <iostream>
#include "EventTracker.hpp"

bool Transporter::send(const std::vector<std::string>& events) {
    const std::string& server_endpoint = EventTracker::getServerEndPoint();

    if (server_endpoint.empty()) {
        std::cerr << "Error: Server endpoint is empty.\n";
        return false;
    }

    // Combine events into a single JSON array string
    std::string jsonArray = "[";
    for (size_t i = 0; i < events.size(); ++i) {
        jsonArray += events[i];
        if (i != events.size() - 1)
            jsonArray += ",";
    }
    jsonArray += "]";

    if (EventTracker::isTestMode()) {
        std::cout << "[TEST MODE] Batched Event Payload:\n" << jsonArray << std::endl;
        return true;
    }

    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Error: Failed to initialize CURL.\n";
        return false;
    }

    curl_easy_setopt(curl, CURLOPT_URL, server_endpoint.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonArray.c_str());

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "CURL Error: " << curl_easy_strerror(res) << std::endl;
        return false;
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    return true;
}