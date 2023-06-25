/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Timer.cpp
*/

#include <sstream>
#include <iomanip>
#include "../includes/Timer.hpp"

using namespace ZappyGui;

Timer::Timer(): _started(false) {}

void Timer::start() {
    _started = true;
    _time = std::chrono::high_resolution_clock::now();
}

void Timer::stop() {
    _started = false;
}

void Timer::reset() {
    _time = std::chrono::high_resolution_clock::now();
}

double Timer::elapsed() const {
    if (_started == false)
        return 0.0;
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - _time);
    return static_cast<double>(duration.count());
}

std::string Timer::elapsedFormatted(const std::string &format) const {
    size_t pos;
    std::string formatted = format;

    int total_seconds = static_cast<int>(elapsed());
    int hours = total_seconds / 3600;
    int minutes = (total_seconds % 3600) / 60;
    int seconds = total_seconds % 60;

    if (_started == false) {
        while((pos = formatted.find("%H")) != std::string::npos) {
            formatted.replace(pos, 2, "00");
        }
        while((pos = formatted.find("%M")) != std::string::npos) {
            formatted.replace(pos, 2, "00");
        }
        while((pos = formatted.find("%S")) != std::string::npos) {
            formatted.replace(pos, 2, "00");
        }
        return formatted;
    }

    while((pos = formatted.find("%H")) != std::string::npos) {
        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << hours;
        formatted.replace(pos, 2, ss.str());
    }
    while((pos = formatted.find("%M")) != std::string::npos) {
        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << minutes;
        formatted.replace(pos, 2, ss.str());
    }
    while((pos = formatted.find("%S")) != std::string::npos) {
        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << seconds;
        formatted.replace(pos, 2, ss.str());
    }

    return formatted;
}
