#pragma once

#include <iostream>

namespace my {
    enum Resource {
        PLAYER,
        FOOD,
        LINEMATE,
        DERAUMERE,
        SIBUR,
        MENDIANE,
        PHIRAS,
        THYSTAME,
        NONE
    };

    std::string typeToString(Resource type);
}
