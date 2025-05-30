#include "Transporter.hpp"
#include <curl/curl.h>
#include <iostream>
#include "EventTracker.hpp"

void Transporter::send(const std::string& jsonPayload) {
    std::string& server_endpoint = EventTracker::getServerEndPoint();
    CURL* curl = curl_easy_init();
    if (!curl && server_endpoint.empty())
        return;

    curl_easy_setopt(curl, CURLOPT_URL, server_endpoint.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonPayload.c_str());

    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
        std::cerr << "CURL Error: " << curl_easy_strerror(res) << std::endl;

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
}