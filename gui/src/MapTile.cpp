#include "../includes/map/MapTile.hpp"

using namespace ZappyGui;

MapTile::MapTile(const Cube &cube): _cube(cube) {
}

const Cube MapTile::getCube() const {
    return this->_cube;
}

MapTile::~MapTile() {}
