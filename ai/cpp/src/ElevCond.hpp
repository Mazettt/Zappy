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

            int get(int currentLevel, ServerLink::Type type) const;

        protected:
        private:
            std::map<ServerLink::Type, int> _one_two;
            std::map<ServerLink::Type, int> _two_three;
            std::map<ServerLink::Type, int> _three_four;
            std::map<ServerLink::Type, int> _four_five;
            std::map<ServerLink::Type, int> _five_six;
            std::map<ServerLink::Type, int> _six_seven;
            std::map<ServerLink::Type, int> _seven_eight;
    };
}
