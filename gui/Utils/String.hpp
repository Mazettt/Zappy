#pragma once

#include <iostream>
#include <vector>

namespace ZappyGui {
    std::vector<std::string> split(const std::string &str, const char &delimiter);
    std::vector<std::string> split(const std::string &str, const std::string &delimiter);
}
