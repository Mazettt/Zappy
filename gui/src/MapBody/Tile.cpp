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

void Tile::addResource(const ResourceManager &manager, IResource::resourceType type) {
    int decalage = -0.42; // TODO

    if (_availablePositions.empty()) {
        this->_resources.push_back(FactoryResource::createResource(type, {decalage + this->_cube.getPos().x, 0.08, decalage + this->_cube.getPos().z}, manager));
        return;
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(_availablePositions.begin(), _availablePositions.end(), g);

    auto [x_index, z_index] = _availablePositions.back();
    _availablePositions.pop_back();
    float x_pos = decalage + x_index * 0.12;
    float z_pos = decalage + z_index * 0.12;
    this->_resources.push_back(FactoryResource::createResource(type, {x_pos + this->_cube.getPos().x, 0.08, z_pos + this->_cube.getPos().z}, manager));
}

void Tile::addPlayer(const ResourceManager &manager, IResource::resourceType type, const PlayerArguments &playerArgs) {
    auto &model = manager.getModel(type);
    auto &texture = manager.getTexture(type);
    this->_players.push_back(std::make_unique<Player>(playerArgs, model, texture));
}

void Tile::draw() {
    this->_cube.draw();

    int nbrResource = this->_resources.size();
    for (int i = 0; i < nbrResource; ++i) {
        this->_resources.at(i)->draw();
    }
    int nbrPlayer = this->_players.size();
    for (int i = 0; i < nbrPlayer; ++i) {
        this->_players.at(i)->draw();
    }
}

Tile::~Tile() {}
