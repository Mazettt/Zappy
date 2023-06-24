#pragma once

#include <iostream>
#include <unordered_map>
#include "ServerLink.hpp"

namespace my {
    class ElevCond {
        public:
            ElevCond();
            ElevCond(const ElevCond &other) = default;
            ElevCond(ElevCond &&other) = default;
            ~ElevCond();

            ElevCond &operator=(const ElevCond &other) = default;
            ElevCond &operator=(ElevCond &&other) = default;

            int get(int currentLevel, Resource type) const;

        protected:
        private:
            std::unordered_map<Resource, int> _one_two;
            std::unordered_map<Resource, int> _two_three;
            std::unordered_map<Resource, int> _three_four;
            std::unordered_map<Resource, int> _four_five;
            std::unordered_map<Resource, int> _five_six;
            std::unordered_map<Resource, int> _six_seven;
            std::unordered_map<Resource, int> _seven_eight;
    };
}
