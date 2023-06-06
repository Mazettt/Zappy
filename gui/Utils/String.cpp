#include "String.hpp"

std::vector<std::string> ZappyGui::split(const std::string &str, const char &delimiter) {
    std::vector<std::string> result;
    std::string tmp;

    for (const char &c : str) {
        if (c == delimiter) {
            if (tmp != "")
                result.push_back(tmp);
            tmp.clear();
        } else
            tmp += c;
    }
    if (tmp != "")
        result.push_back(tmp);
    return result;
}

std::vector<std::string> ZappyGui::split(const std::string &str, const std::string &delimiter) {
    std::vector<std::string> result;
    std::string tmp;

    for (const char &c : str) {
        if (delimiter.find(c) != std::string::npos) {
            if (tmp != "")
                result.push_back(tmp);
            tmp.clear();
        } else
            tmp += c;
    }
    if (tmp != "")
        result.push_back(tmp);
    return result;
}
