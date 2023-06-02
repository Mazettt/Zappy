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

void Tile::addResource(IResource::resourceType type) {
    if (_availablePositions.empty()) {
        this->_resources.push_back({ type, 0.0, 0.0 });
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(_availablePositions.begin(), _availablePositions.end(), g);

    auto [x_index, z_index] = _availablePositions.back();
    _availablePositions.pop_back();
    float x_pos = -0.42 + x_index * 0.12;
    float z_pos = -0.42 + z_index * 0.12;
    this->_resources.push_back({ type, x_pos, z_pos });
}

// void addPlayer() player -> vector

void Tile::draw(const FactoryResource &factory) {
    this->_cube.draw();

    // resource
    int nbrResource = this->_resources.size();
    for (int i = 0; i < nbrResource; ++i) {
        std::tuple<IResource::resourceType, float, float> resource = this->_resources.at(i);
        IResource::resourceType type = std::get<0>(resource);
        float x_pos = std::get<1>(resource);
        float z_pos = std::get<2>(resource);
        factory.getResourceMap().at(type)->setPosition(x_pos, z_pos);
        factory.getResourceMap().at(type)->draw();
    }
    //player if exist
}

Tile::~Tile() {}
