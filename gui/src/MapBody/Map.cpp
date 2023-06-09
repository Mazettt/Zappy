/*
** EPITECH PROJECT, 2022
** gui
** File description:
** map.cpp
*/

#include "../../includes/MapHeader/Map.hpp"

using namespace ZappyGui;

Map::Map(int x, int y, ResourceManager &manager): _manager(manager) {
    float widthCube = 1.0;
    float lengthCube = 1.0;
    float heightCube = 0.1;
    this->_size.x = x;
    this->_size.y = y;
    this->_map.resize(x * y);
    _manager.initialize();

    Color color = {120, 80, 160, 140};
    for (int y = 0; y < this->_size.y; ++y) {
        for (int x = 0; x < this->_size.x; ++x) {
            int key = y * this->_size.x + x;
            Vector3 cubePosition = { widthCube * x, 0.0f, lengthCube * y };
            Cube cube(cubePosition, widthCube, heightCube, lengthCube, color);
            std::shared_ptr<Tile> tile = std::make_shared<Tile>(cube);
            this->_map[key] = std::move(tile);
            this->_map[key]->addResource(this->_manager, IResource::resourceType::EGG);
            this->_map[key]->addResource(this->_manager, IResource::resourceType::BURGER);
            this->_map[key]->addResource(this->_manager, IResource::resourceType::MENDIANE);
        }
    }
    PlayerArguments playerArgs(0, "Team1", {3.0f, 0.0f, 8.0f}, {1.0f, 0.0f, 0.0f}, -90.0f, {0.6f, 0.6f, 0.6f}, 0 , 3);
    this->addPlayerForTile(playerArgs);
    PlayerArguments playerArgs1(1, "Team1", {5.0f, 0.0f, 7.0f}, {1.0f, 0.0f, 0.0f}, -90.0f, {0.6f, 0.6f, 0.6f}, 0 , 1);
    this->addPlayerForTile(playerArgs1);
    PlayerArguments playerArgs2(2, "Team1", {8.0f, 0.0f, 3.0f}, {1.0f, 0.0f, 0.0f}, -90.0f, {0.6f, 0.6f, 0.6f}, 0 , 3);
    this->addPlayerForTile(playerArgs2);
    PlayerArguments playerArgs3(3, "Team1", {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, -90.0f, {0.6f, 0.6f, 0.6f}, 0 , 1);
    this->addPlayerForTile(playerArgs3);
}

void Map::addResourceForTile(const Vector2 &pos, IResource::resourceType type) {
    this->_map[pos.y * this->_size.x + pos.x]->addResource(this->_manager, type);
}

void Map::addPlayerForTile(const PlayerArguments &playerArgs) {
    auto &modelPlayer = this->_manager.getPlayerModel();
    auto &texture = this->_manager.getTexture(IResource::resourceType::PLAYER);
    auto &animation = this->_manager.getAnimation(IResource::resourceType::PLAYER);
    this->_players.push_back(std::make_unique<Player>(playerArgs, modelPlayer, texture, animation));
}

void Map::movePlayer(int playerNumber, float x, float z) {
    int nbrPlayer = this->_players.size();
    for (int i = 0; i < nbrPlayer; ++i) {
        if (this->_players.at(i)->getPlayerNumber() == playerNumber) {
            Vector3 pos = this->_players.at(i)->getPosition();
            this->_players.at(i)->_movePos = {x - pos.x, 0.0, z - pos.z};
            // orientation
            this->_players.at(i)->animationWalk();
        }
    }
}

void Map::deadPlayer(int playerNumber) {
    int nbrPlayer = this->_players.size();
    for (int i = 0; i < nbrPlayer; ++i) {
        if (this->_players.at(i)->getPlayerNumber() == playerNumber) {
            this->_players.at(i)->animationDie();
        }
    }
}

void Map::draw() {
    for (int y = 0; y < this->_size.y; ++y) {
        for (int x = 0; x < this->_size.x; ++x) {
            int key = y * this->_size.x + x;
            std::shared_ptr<Tile> &tile = this->_map.at(key);
            tile->draw();
        }
    }

    float moveSpeed = 0.06;
    int nbrPlayer = this->_players.size();
    for (int i = 0; i < nbrPlayer; ++i) {
        Vector3 pos = this->_players.at(i)->getPosition();
        if (this->_players.at(i)->_movePos.x > 0.0) {
            this->_players.at(i)->setPosition({ pos.x += moveSpeed, 0.0, pos.z });
            this->_players.at(i)->_movePos.x -= moveSpeed;
        }
        if (this->_players.at(i)->_movePos.z > 0.0) {
            this->_players.at(i)->setPosition({ pos.x, 0.0, pos.z += moveSpeed });
            this->_players.at(i)->_movePos.z -= moveSpeed;
        }
        if (this->_players.at(i)->_movePos.x < 0.0) {
            this->_players.at(i)->setPosition({ pos.x -= moveSpeed, 0.0, pos.z });
            this->_players.at(i)->_movePos.x += moveSpeed;
        }
        if (this->_players.at(i)->_movePos.z < 0.0) {
            this->_players.at(i)->setPosition({ pos.x, 0.0, pos.z -= moveSpeed });
            this->_players.at(i)->_movePos.z += moveSpeed;
        }
        float epsilon = 0.0001f;
        if (abs(this->_players.at(i)->_movePos.x) < epsilon && abs(this->_players.at(i)->_movePos.z) < epsilon) {
            if (this->_players.at(i)->getAnimationType() == Player::animationPlayerType::PLAYER_WALK) {
                this->_players.at(i)->animationWait();
            }
            if (this->_players.at(i)->_animationCounter > 0) {
                this->_players.at(i)->_animationCounter -= 1;
            } else if (this->_players.at(i)->_animationCounter <= 0) {
                if (this->_players.at(i)->getAnimationType() == Player::animationPlayerType::PLAYER_DIE) {
                    this->_players.erase(this->_players.begin() + i);
                    nbrPlayer -= 1;
                    continue;
                } else {
                    this->_players.at(i)->setAnimationType(Player::animationPlayerType::PLAYER_WAIT);
                }
            }
        }
        this->_players.at(i)->draw();
    }
}

Map::~Map() {}
