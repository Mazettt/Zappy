#include "ElevCond.hpp"

using namespace my;

ElevCond::ElevCond() {
    _one_two = {
        {ServerLink::Type::PLAYER, 1},
        {ServerLink::Type::LINEMATE, 1},
        {ServerLink::Type::DERAUMERE, 0},
        {ServerLink::Type::SIBUR, 0},
        {ServerLink::Type::MENDIANE, 0},
        {ServerLink::Type::PHIRAS, 0},
        {ServerLink::Type::THYSTAME, 0}
    };
    _two_three = {
        {ServerLink::Type::PLAYER, 2},
        {ServerLink::Type::LINEMATE, 1},
        {ServerLink::Type::DERAUMERE, 1},
        {ServerLink::Type::SIBUR, 1},
        {ServerLink::Type::MENDIANE, 0},
        {ServerLink::Type::PHIRAS, 0},
        {ServerLink::Type::THYSTAME, 0}
    };
    _three_four = {
        {ServerLink::Type::PLAYER, 2},
        {ServerLink::Type::LINEMATE, 2},
        {ServerLink::Type::DERAUMERE, 0},
        {ServerLink::Type::SIBUR, 1},
        {ServerLink::Type::MENDIANE, 0},
        {ServerLink::Type::PHIRAS, 2},
        {ServerLink::Type::THYSTAME, 0}
    };
    _four_five = {
        {ServerLink::Type::PLAYER, 4},
        {ServerLink::Type::LINEMATE, 1},
        {ServerLink::Type::DERAUMERE, 1},
        {ServerLink::Type::SIBUR, 2},
        {ServerLink::Type::MENDIANE, 0},
        {ServerLink::Type::PHIRAS, 1},
        {ServerLink::Type::THYSTAME, 0}
    };
    _five_six = {
        {ServerLink::Type::PLAYER, 4},
        {ServerLink::Type::LINEMATE, 1},
        {ServerLink::Type::DERAUMERE, 2},
        {ServerLink::Type::SIBUR, 1},
        {ServerLink::Type::MENDIANE, 3},
        {ServerLink::Type::PHIRAS, 0},
        {ServerLink::Type::THYSTAME, 0}
    };
    _six_seven = {
        {ServerLink::Type::PLAYER, 6},
        {ServerLink::Type::LINEMATE, 1},
        {ServerLink::Type::DERAUMERE, 2},
        {ServerLink::Type::SIBUR, 3},
        {ServerLink::Type::MENDIANE, 0},
        {ServerLink::Type::PHIRAS, 1},
        {ServerLink::Type::THYSTAME, 0}
    };
    _seven_eight = {
        {ServerLink::Type::PLAYER, 6},
        {ServerLink::Type::LINEMATE, 2},
        {ServerLink::Type::DERAUMERE, 2},
        {ServerLink::Type::SIBUR, 2},
        {ServerLink::Type::MENDIANE, 2},
        {ServerLink::Type::PHIRAS, 2},
        {ServerLink::Type::THYSTAME, 1}
    };
}

ElevCond::~ElevCond() {}

int ElevCond::get(int currentLevel, ServerLink::Type type) const {
    switch (currentLevel) {
        case 1:
            return _one_two.at(type);
        case 2:
            return _two_three.at(type);
        case 3:
            return _three_four.at(type);
        case 4:
            return _four_five.at(type);
        case 5:
            return _five_six.at(type);
        case 6:
            return _six_seven.at(type);
        case 7:
            return _seven_eight.at(type);
        default:
            return 0;
    }
}
