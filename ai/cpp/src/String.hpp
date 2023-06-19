#pragma once

#include <iostream>
#include <vector>

namespace my {
    std::vector<std::string> split(const std::string &str, const char &delimiter);
    std::vector<std::string> split(const std::string &str, const std::string &delimiter);
    std::vector<std::string> splitWithEmpty(const std::string &str, const char &delimiter);
    std::vector<std::string> splitWithEmpty(const std::string &str, const std::string &delimiter);
}
