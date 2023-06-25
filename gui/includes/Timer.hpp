/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Timer.h
*/

#pragma once

#include <chrono>
#include <string>

namespace ZappyGui {
    class Timer {
        private:
            bool _started;
            std::chrono::high_resolution_clock::time_point _time;

        public:
            Timer();
            void start();
            void stop();
            void reset();
            double elapsed() const;
            std::string elapsedFormatted(const std::string &format) const;
    };
}
