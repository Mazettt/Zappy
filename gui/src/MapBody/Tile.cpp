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
    this->_resources.push_back(FactoryResource::createResource(type, {x_pos + this->_cube.getPos().x, 0.08, z_pos + this->_cube.getPos().z}, manager));
}

void Tile::addPlayer(const ResourceManager &manager, IResource::resourceType type) {
    const MyRayLib::Model &model = manager.getModel(type);
    const MyRayLib::Texture2D &texture = manager.getTexture(type);
    PlayerArguments playerArgs(5, 2, "Team1", {0.0f, 0.0f, 0.0f}, -90.0f, {0.6f, 0.6f, 0.6f}, {1.0f, 0.0f, 0.0f}, 0);
    this->_players.push_back(std::make_unique<Player>(playerArgs, model, texture));
}

void Tile::draw() {
    this->_cube.draw();

    // resource
    int nbrResource = this->_resources.size();
    for (int i = 0; i < nbrResource; ++i) {
        this->_resources.at(i)->draw();
    }
    //player if exist
    int nbrPlayer = this->_players.size();
    for (int i = 0; i < nbrPlayer; ++i) {
        this->_players.at(i)->draw();
    }
}

Tile::~Tile() {}
