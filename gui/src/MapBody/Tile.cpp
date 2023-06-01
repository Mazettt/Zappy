#include "../../includes/MapHeader/Tile.hpp"
#include "../../includes/resources/FactoryResource.hpp"

using namespace ZappyGui;

Tile::Tile(const Cube &cube): _cube(cube) {
    this->_Resources.resize(7);
    int i = 0;
    this->_Resources[i++] = std::make_pair(FactoryResource::createResource("food"), 0);
    // this->_Resources[i+] = std::make_pair(FactoryResource::createResource("linemate"), 0);
    // this->_Resources[i+] = std::make_pair(FactoryResource::createResource("deraumere"), 0);
    // this->_Resources[i+] = std::make_pair(FactoryResource::createResource("sibur"), 0);
    // this->_Resources[i+] = std::make_pair(FactoryResource::createResource("mendiane"), 0);
    // this->_Resources[i+] = std::make_pair(FactoryResource::createResource("phiras"), 0);
    // this->_Resources[i+] = std::make_pair(FactoryResource::createResource("thystame"), 0);
}

const Cube Tile::getCube() const {
    return this->_cube;
}

void Tile::addResource(int keyResource, int quantity) {
    this->_Resources[keyResource].second += quantity;
}

Tile::~Tile() {}
