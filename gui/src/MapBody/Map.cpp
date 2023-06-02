/*
** EPITECH PROJECT, 2022
** gui
** File description:
** map.cpp
*/

#include "../../includes/MapHeader/Map.hpp"

using namespace ZappyGui;

Map::Map(int x, int y): _factory(FactoryResource()) {
    float widthCube = 1.0;
    float lengthCube = 1.0;
    float heightCube = 0.1;
    this->_sizeX = x;
    this->_sizeY = y;
    this->_map.resize(x * y);

    int i = 0;
    Color color = RED;
    for (int y = 0; y < this->_sizeY; ++y) {
        for (int x = 0; x < this->_sizeX; ++x) {
            int key = y * this->_sizeX + x;
            Vector3 cubePosition = { widthCube * x, 0.0f, lengthCube * y };
            Cube cube(cubePosition, widthCube, heightCube, lengthCube, color);
            std::shared_ptr<Tile> tile = std::make_shared<Tile>(cube);
            this->_map[key] = std::move(tile);
            this->_map[key]->addResource(IResource::resourceType::DERAUMERE);
            this->_map[key]->addResource(IResource::resourceType::LINEMATE);
        }
    }
}

std::vector<std::shared_ptr<Tile>> Map::getMap() {
    return this->_map;
}

std::shared_ptr<Tile> &Map::getTile(int key) {
    return this->_map.at(key);
}

void Map::addResourceForTile(int posX, int posY, IResource::resourceType type) {
    this->_map[posY * this->_sizeX + posX]->addResource(type);
}

void Map::draw() {
    for (int y = 0; y < this->_sizeY; ++y) {
        for (int x = 0; x < this->_sizeX; ++x) {
            int key = y * this->_sizeX + x;
            std::shared_ptr<Tile> &tile = this->_map.at(key);
            tile->draw(this->_factory);
        }
    }
}

Map::~Map() {}
