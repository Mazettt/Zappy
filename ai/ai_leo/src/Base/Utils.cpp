#include "Utils.hpp"

std::string my::typeToString(my::Resource type) {
    switch (type) {
        case my::Resource::PLAYER:
            return "player";
        case my::Resource::FOOD:
            return "food";
        case my::Resource::LINEMATE:
            return "linemate";
        case my::Resource::DERAUMERE:
            return "deraumere";
        case my::Resource::SIBUR:
            return "sibur";
        case my::Resource::MENDIANE:
            return "mendiane";
        case my::Resource::PHIRAS:
            return "phiras";
        case my::Resource::THYSTAME:
            return "thystame";
        default:
            return "none";
    }
}
