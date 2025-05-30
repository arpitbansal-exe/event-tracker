#pragma once

#include <string>

class Transporter {
public:
    static void send(const std::string& jsonPayload);
};