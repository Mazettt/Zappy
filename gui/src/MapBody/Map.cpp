/*
** EPITECH PROJECT, 2022
** gui
** File description:
** map.cpp
*/

#include "../../includes/MapHeader/Map.hpp"

using namespace ZappyGui;

Map::Map(int x, int y): _manager(ResourceManager()) {
    float widthCube = 1.0;
    float lengthCube = 1.0;
    float heightCube = 0.1;
    this->_size.x = x;
    this->_size.y = y;
    this->_map.resize(x * y);

    Color color = RED;
    for (int y = 0; y < this->_size.y; ++y) {
        for (int x = 0; x < this->_size.x; ++x) {
            int key = y * this->_size.x + x;
            Vector3 cubePosition = { widthCube * x, 0.0f, lengthCube * y };
            Cube cube(cubePosition, widthCube, heightCube, lengthCube, color);
            std::shared_ptr<Tile> tile = std::make_shared<Tile>(cube);
            this->_map[key] = std::move(tile);
            this->_map[key]->addResource(this->_manager, IResource::resourceType::SIBUR);
            this->_map[key]->addResource(this->_manager, IResource::resourceType::LINEMATE);
            this->_map[key]->addResource(this->_manager, IResource::resourceType::MENDIANE);
        }
    }
    PlayerArguments playerArgs(5, 2, "Team1", {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, 10.0f, {0.6f, 0.6f, 0.6f}, 0 , 3);
    this->addPlayerForTile({1.0f, 0.0f}, playerArgs);

    PlayerArguments playerArgs1(5, 2, "Team1", {5.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, 10.0f, {0.6f, 0.6f, 0.6f}, 0 , 1);
    this->addPlayerForTile({1.0f, 0.0f}, playerArgs1);
}

void Map::addResourceForTile(const Vector2 &pos, IResource::resourceType type) {
    this->_map[pos.y * this->_size.x + pos.x]->addResource(this->_manager, type);
}

void Map::addPlayerForTile(const Vector2 &pos, const PlayerArguments &playerArgs) {
    auto &modelPlayer = this->_manager.getPlayerModel();
    auto &texture = this->_manager.getTexture(IResource::resourceType::PLAYER);
    auto &animation = this->_manager.getAnimation(IResource::resourceType::PLAYER);
    this->_players.push_back(std::make_unique<Player>(playerArgs, modelPlayer, texture, animation));
}


void Map::draw() {
    for (int y = 0; y < this->_size.y; ++y) {
        for (int x = 0; x < this->_size.x; ++x) {
            int key = y * this->_size.x + x;
            std::shared_ptr<Tile> &tile = this->_map.at(key);
            tile->draw();
        }
    }
    int nbrPlayer = this->_players.size();
    for (int i = 0; i < nbrPlayer; ++i) {
        this->_players.at(i)->draw();
    }
}

Map::~Map() {}
