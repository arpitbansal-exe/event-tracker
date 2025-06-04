#pragma once

#include <string>
#include <vector>
class Transporter {
public:
    static bool send(const std::vector<std::string>& events);
};