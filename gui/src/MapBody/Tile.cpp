#include <random>
#include <algorithm>
#include "../../includes/MapHeader/Tile.hpp"

using namespace ZappyGui;

Tile::Tile(const Cube &cube): _cube(cube) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            _availablePositions.push_back({i, j});
        }
    }
}

const Cube Tile::getCube() const {
    return this->_cube;
}

void Tile::addResource(const ResourceManager &manager, IResource::resourceType type) {
    if (_availablePositions.empty()) {
        // this->_resources.push_back({ type, 0.0, 0.0 });
        this->_resources.push_back(FactoryResource::createResource(type, {0.0, 0.0, 0.0}, manager));
        return;
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(_availablePositions.begin(), _availablePositions.end(), g);

    auto [x_index, z_index] = _availablePositions.back();
    _availablePositions.pop_back();
    float x_pos = -0.42 + x_index * 0.12;
    float z_pos = -0.42 + z_index * 0.12;
    // FactoryResource::createResource(type, {x_pos, 0.0, z_pos}, manager);
    // auto test = FactoryResource::createResource(type, {x_pos, 0.0, z_pos}, manager);
    this->_resources.push_back(FactoryResource::createResource(type, {x_pos + this->_cube.getPos().x, 0.08, z_pos + this->_cube.getPos().z}, manager));
}

// void addPlayer() player -> vector

void Tile::draw() {
    this->_cube.draw();

    // resource
    int nbrResource = this->_resources.size();
    for (int i = 0; i < nbrResource; ++i) {
        this->_resources.at(i)->draw();
    }
    //player if exist
}

Tile::~Tile() {}
