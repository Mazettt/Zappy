#pragma once

#include <iostream>
#include <map>
#include "ServerLink.hpp"

namespace my {
    class ElevCond {
        public:
            ElevCond();
            ElevCond(const ElevCond &other) = delete;
            ElevCond(ElevCond &&other) = delete;
            ~ElevCond();

            ElevCond &operator=(const ElevCond &other) = delete;
            ElevCond &operator=(ElevCond &&other) = delete;

            int get(int currentLevel, Resource type) const;

        protected:
        private:
            std::map<Resource, int> _one_two;
            std::map<Resource, int> _two_three;
            std::map<Resource, int> _three_four;
            std::map<Resource, int> _four_five;
            std::map<Resource, int> _five_six;
            std::map<Resource, int> _six_seven;
            std::map<Resource, int> _seven_eight;
    };
}
