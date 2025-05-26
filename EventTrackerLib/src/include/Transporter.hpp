#pragma once

#include <string>

class Transporter {
public:
    static void send(const std::string& server_endpoint, const std::string& jsonPayload);
};