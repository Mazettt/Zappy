/*
** EPITECH PROJECT, 2022
** gui
** File description:
** map.cpp
*/

#include <cmath>
#include <cassert>
#include <algorithm>
#include "../../includes/MapHeader/Map.hpp"
#include "../../Utils/MyError.hpp"

using namespace ZappyGui;

Map::Map(ResourceManager &manager, MyRayLib::FreeCamera &camera, ServerLink &link): _manager(manager), _camera(camera), _selectedTileKey(-1), _link(link) {}

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
    p->addOnInventory(type, 1);
    assert(key < this->_map.size());
    this->_map.at(key)->removeResource(type);
}

void Map::setPlayerLevel(int playerID, int level) {
    std::shared_ptr<Player> p = this->findPlayerByID(playerID);

    p->setPlayerLevel(level);
}

void Map::updateResourceForTile(const Vector2 &pos, IResource::resourceType type, int number) {
    int count = 0;
    const int key = pos.y * this->_size.x + pos.x;

    for (const auto &r : this->_map[key]->_resources)
        if (r->getType() == type)
            count++;
    while (count > number) {
        this->_map[key]->removeResource(type);
        count--;
    }
    while (count < number) {
        this->_map[key]->addResource(this->_manager, type);
        count++;
    }
}

void Map::addEggForTile(const Vector2 &pos, int id) {
    const int key = pos.y * this->_size.x + pos.x;

    this->_map[key]->addEgg(this->_manager, id);
}

void Map::removeEgg(int id) {
    for (auto &tile : this->_map)
        tile->removeEgg(id);
}

void Map::addPlayerForTile(const PlayerArguments &playerArgs) {
    auto &modelPlayer = this->_manager.getNoneConstModel(IResource::resourceType::PLAYER);
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

void Map::update(float deltaTime) {
    for (auto it = this->_players.begin(); it != this->_players.end();) {
        std::shared_ptr<Player> player = *it;
        if (player->update(deltaTime)) {
            it = this->_players.erase(it);
            continue;
        }
        ++it;
    }
}

void Map::draw() {
    const bool pressed = IsMouseButtonPressed(MOUSE_BUTTON_RIGHT);
    bool hit = false;
    for (int y = 0; y < this->_size.y; ++y) {
        for (int x = 0; x < this->_size.x; ++x) {
            int key = y * this->_size.x + x;
            std::shared_ptr<Tile>& tile = this->_map.at(key);

            if (pressed) {
                Vector3 cubePosition = tile->_cube.getPos();
                Vector3 cubeSize = {tile->_cube.getWidth(), tile->_cube.getHeight(), tile->_cube.getLength()};
                BoundingBox box = {(Vector3){ cubePosition.x - cubeSize.x / 2, cubePosition.y - cubeSize.y / 2, cubePosition.z - cubeSize.z / 2 },
                                   (Vector3){ cubePosition.x + cubeSize.x / 2, cubePosition.y + cubeSize.y / 2, cubePosition.z + cubeSize.z / 2 }};
                if (GetRayCollisionBox(GetMouseRay(GetMousePosition(), this->_camera.getCamera()), box).hit) {
                    _selectedTileKey = _selectedTileKey == key ? -1 : key;
                    hit = true;
                    this->_link.askTileContent(cubePosition.x, cubePosition.z);
                }
            }
            tile->draw();
        }
    }
    if (pressed && !hit)
        _selectedTileKey = -1;
    for (int y = 0; y < this->_size.y; ++y) {
        for (int x = 0; x < this->_size.x; ++x) {
            int key = y * this->_size.x + x;
            std::shared_ptr<Tile>& tile = this->_map.at(key);

            if (key == _selectedTileKey) {
                this->_camera.endMode3D();
                tile->drawContentPopup(this->_manager.getTexture(IResource::resourceType::POPUPTILE));
                this->_camera.beginMode3D();
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
    for (auto it = this->_players.begin(); it != this->_players.end(); ++it) {
        std::shared_ptr<Player> player = *it;
        player->draw();
    }
}

void Map::updatePlayerInventory(int id, int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame)
{
    this->_players.at(id)->setInventory(food, linemate, deraumere, sibur, mendiane, phiras, thystame);
}

void Map::resetGame() {
    this->_players.clear();
}

Map::~Map() {
    this->_players.clear();
}
