/*
** EPITECH PROJECT, 2022
** gui
** File description:
** map.cpp
*/

#include <cmath>
#include <algorithm>
#include "../../includes/MapHeader/Map.hpp"

using namespace ZappyGui;

Map::Map(ResourceManager &manager, const MyRayLib::FreeCamera &camera): _manager(manager), _camera(camera), _selectedTileKey(-1) {}

std::shared_ptr<Player> Map::findPlayerByID(int id) {
    for (std::shared_ptr<Player> p : this->_players) {
        if (p->getPlayerNumber() == id) {
            return p;
        }
    }
    return nullptr;
}

void Map::createMap(int x, int y) {
    float widthCube = 1.0;
    float lengthCube = 1.0;
    float heightCube = 0.1;
    this->_size.x = x;
    this->_size.y = y;
    this->_map.resize(x * y);

    Color color = {120, 80, 160, 140};
    for (int y = 0; y < this->_size.y; ++y) {
        for (int x = 0; x < this->_size.x; ++x) {
            int key = y * this->_size.x + x;
            Vector3 cubePosition = { widthCube * x, 0.0f, lengthCube * y };
            Cube cube(cubePosition, widthCube, heightCube, lengthCube, color);
            std::shared_ptr<Tile> tile = std::make_shared<Tile>(cube);
            this->_map[key] = std::move(tile);
        }
    }
}

void Map::StartPlayersLeveling(std::vector<int> playersID, int level, float x, float z) {
    for (std::shared_ptr<Player> p : this->_players) {
        if (std::find(playersID.begin(), playersID.end(), p->getPlayerNumber()) != playersID.end()) {
            p->setPlayerLevel(level);
            p->setPosition({ x, 0.0, z });
            p->animationLVLUP();
        }
    }
}

void Map::EndPlayersLeveling(float x, float z, bool result) {
    (void) result;
    for (std::shared_ptr<Player> p : this->_players) {
        Vector3 pos = p->getPosition();
        if (pos.x == x && pos.z == z) {
            p->animationWait(); // TODO animation if success or not
        }
    }
}

void Map::dropResource(int playerID, IResource::resourceType type) {
    std::shared_ptr<Player> p = this->findPlayerByID(playerID);
    Vector3 pos = p->getPosition();
    int key = std::round(pos.z * this->_size.x + pos.x);

    p->removeOnInventory(type, 1);
    this->_map.at(key)->addResource(this->_manager, type);
}

void Map::collectResource(int playerID, IResource::resourceType type) {
    std::shared_ptr<Player> p = this->findPlayerByID(playerID);
    Vector3 pos = p->getPosition();
    int key = std::round(pos.z * this->_size.x + pos.x);
    std::cout << "player pos: " << pos.x << " " << pos.y << " " << pos.z  << " -> key: " << key << std::endl;
    p->addOnInventory(type, 1);
    this->_map.at(key)->removeResource(type);
}

bool Map::setPlayerLevel(int playerID, int level) {
    std::shared_ptr<Player> p = this->findPlayerByID(playerID);

    p->setPlayerLevel(level);
}

void Map::addResourceForTile(const Vector2 &pos, IResource::resourceType type, int number) {
    while (number--) {
        this->_map[pos.y * this->_size.x + pos.x]->addResource(this->_manager, type);
    }
}

void Map::addPlayerForTile(const PlayerArguments &playerArgs) {
    auto &modelPlayer = this->_manager.getPlayerModel();
    auto &texture = this->_manager.getTexture(IResource::resourceType::PLAYER);
    auto &animation = this->_manager.getAnimation(IResource::resourceType::PLAYER);
    this->_players.push_back(std::make_shared<Player>(playerArgs, modelPlayer, texture, animation));
}

bool Map::movePlayer(int playerID, float x, float z, Player::orientationAxis orientation) {
    std::shared_ptr<Player> p = this->findPlayerByID(playerID);

    if (p != nullptr) {
        Vector3 pos = p->getPosition();
        p->_movePos = {x - pos.x, 0.0, z - pos.z};
        p->setRotationAngle((float)orientation);
        p->animationWalk();
        return true;
    }
    return false;
}

bool Map::deadPlayer(int playerID) {
    std::shared_ptr<Player> p = this->findPlayerByID(playerID);

    if (p != nullptr) {
        p->animationDie();
        return true;
    }
    return false;
}

void Map::draw() {
    bool hit = false;
    for (int y = 0; y < this->_size.y; ++y) {
        for (int x = 0; x < this->_size.x; ++x) {
            int key = y * this->_size.x + x;
            std::shared_ptr<Tile>& tile = this->_map.at(key);

            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
            {
                Vector3 cubePosition = tile->_cube.getPos();
                Vector3 cubeSize = {tile->_cube.getWidth(), tile->_cube.getHeight(), tile->_cube.getLength()};
                BoundingBox box = {(Vector3){ cubePosition.x - cubeSize.x / 2, cubePosition.y - cubeSize.y / 2, cubePosition.z - cubeSize.z / 2 },
                                   (Vector3){ cubePosition.x + cubeSize.x / 2, cubePosition.y + cubeSize.y / 2, cubePosition.z + cubeSize.z / 2 }};
                if (GetRayCollisionBox(GetMouseRay(GetMousePosition(), _camera.getCamera()), box).hit) {
                    _selectedTileKey = _selectedTileKey == key ? -1 : key;
                    hit = true;
                }
            }
            tile->draw();
        }
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !hit)
        _selectedTileKey = -1;
    for (int y = 0; y < this->_size.y; ++y) {
        for (int x = 0; x < this->_size.x; ++x) {
            int key = y * this->_size.x + x;
            std::shared_ptr<Tile>& tile = this->_map.at(key);

            if (key == _selectedTileKey) {
                tile->_cube._color.r = 255;
                tile->_cube._color.g = 0;
                tile->_cube._color.b = 0;
            } else {
                tile->_cube._color.r = 120;
                tile->_cube._color.g = 80;
                tile->_cube._color.b = 160;
            }
        }
    }

    float moveSpeed = 0.06;
    float epsilon = 0.0001f;

    for (auto it = this->_players.begin(); it != this->_players.end();) {
        std::shared_ptr<Player> player = *it;
        Vector3 pos = player->getPosition();
        float moveX = 0.0f;
        float moveZ = 0.0f;

        if (player->_movePos.x > 0.0f) {
            moveX = std::min(moveSpeed, player->_movePos.x);
            player->_movePos.x -= moveX;
        } else if (player->_movePos.x < 0.0f) {
            moveX = std::max(-moveSpeed, player->_movePos.x);
            player->_movePos.x -= moveX;
        }

        if (player->_movePos.z > 0.0f) {
            moveZ = std::min(moveSpeed, player->_movePos.z);
            player->_movePos.z -= moveZ;
        } else if (player->_movePos.z < 0.0f) {
            moveZ = std::max(-moveSpeed, player->_movePos.z);
            player->_movePos.z -= moveZ;
        }

        pos.x += moveX;
        pos.z += moveZ;
        player->setPosition(pos);

        if (std::abs(player->_movePos.x) < epsilon && std::abs(player->_movePos.z) < epsilon) {
            if (player->getAnimationType() == Player::animationPlayerType::PLAYER_WALK) {
                player->animationWait();
            }

            if (player->_animationCounter > 0) {
                player->_animationCounter -= 1;
            } else if (player->_animationCounter <= 0) {
                if (player->getAnimationType() == Player::animationPlayerType::PLAYER_DIE) {
                    it = this->_players.erase(it);
                    continue;
                } else {
                    player->setAnimationType(Player::animationPlayerType::PLAYER_WAIT);
                }
            }
        }

        player->draw();
        ++it;
    }
}


void Map::resetGame() {
    this->_players.clear();
}

Map::~Map() {
    this->_players.clear();
}
