#include "ElevCond.hpp"

using namespace my;

ElevCond::ElevCond() {
    _one_two = {
        {Resource::PLAYER, 1},
        {Resource::FOOD, 0},
        {Resource::LINEMATE, 1},
        {Resource::DERAUMERE, 0},
        {Resource::SIBUR, 0},
        {Resource::MENDIANE, 0},
        {Resource::PHIRAS, 0},
        {Resource::THYSTAME, 0}
    };
    _two_three = {
        {Resource::PLAYER, 2},
        {Resource::FOOD, 0},
        {Resource::LINEMATE, 1},
        {Resource::DERAUMERE, 1},
        {Resource::SIBUR, 1},
        {Resource::MENDIANE, 0},
        {Resource::PHIRAS, 0},
        {Resource::THYSTAME, 0}
    };
    _three_four = {
        {Resource::PLAYER, 2},
        {Resource::FOOD, 0},
        {Resource::LINEMATE, 2},
        {Resource::DERAUMERE, 0},
        {Resource::SIBUR, 1},
        {Resource::MENDIANE, 0},
        {Resource::PHIRAS, 2},
        {Resource::THYSTAME, 0}
    };
    _four_five = {
        {Resource::PLAYER, 4},
        {Resource::FOOD, 0},
        {Resource::LINEMATE, 1},
        {Resource::DERAUMERE, 1},
        {Resource::SIBUR, 2},
        {Resource::MENDIANE, 0},
        {Resource::PHIRAS, 1},
        {Resource::THYSTAME, 0}
    };
    _five_six = {
        {Resource::PLAYER, 4},
        {Resource::FOOD, 0},
        {Resource::LINEMATE, 1},
        {Resource::DERAUMERE, 2},
        {Resource::SIBUR, 1},
        {Resource::MENDIANE, 3},
        {Resource::PHIRAS, 0},
        {Resource::THYSTAME, 0}
    };
    _six_seven = {
        {Resource::PLAYER, 6},
        {Resource::FOOD, 0},
        {Resource::LINEMATE, 1},
        {Resource::DERAUMERE, 2},
        {Resource::SIBUR, 3},
        {Resource::MENDIANE, 0},
        {Resource::PHIRAS, 1},
        {Resource::THYSTAME, 0}
    };
    _seven_eight = {
        {Resource::PLAYER, 6},
        {Resource::FOOD, 0},
        {Resource::LINEMATE, 2},
        {Resource::DERAUMERE, 2},
        {Resource::SIBUR, 2},
        {Resource::MENDIANE, 2},
        {Resource::PHIRAS, 2},
        {Resource::THYSTAME, 1}
    };
}

ElevCond::~ElevCond() {}

int ElevCond::get(int currentLevel, Resource type) const {
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
