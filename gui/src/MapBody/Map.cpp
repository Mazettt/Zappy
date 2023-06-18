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
    this->_size.setX(x);
    this->_size.setY(y);
    this->_map.resize(x * y);

    Color color = {120, 80, 160, 140};
    for (int y = 0; y < this->_size.getY(); ++y) {
        for (int x = 0; x < this->_size.getX(); ++x) {
            int key = y * this->_size.getX() + x;
            MyRayLib::Vector3D cubePosition = { widthCube * x, 0.0f, lengthCube * y };
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
        MyRayLib::Vector3D pos = p->getPosition();
        if (pos.getX() == x && pos.getZ() == z) {
            p->animationWait();
        }
    }
}

void Map::dropResource(int playerID, IResource::resourceType type) {
    std::shared_ptr<Player> p = this->findPlayerByID(playerID);
    MyRayLib::Vector3D pos = p->getPosition();
    int key = std::round(pos.getZ() * this->_size.getX() + pos.getX());

    p->removeOnInventory(type, 1);
    this->_map.at(key)->addResource(this->_manager, type);
}

void Map::collectResource(int playerID, IResource::resourceType type) {
    std::shared_ptr<Player> p = this->findPlayerByID(playerID);
    MyRayLib::Vector3D pos = p->getPosition();
    p->animationGet();
    int key = std::round(pos.getZ() * this->_size.getX() + pos.getX());
    p->addOnInventory(type, 1);
    this->_map.at(key)->removeResource(type);
}

void Map::setPlayerLevel(int playerID, int level) {
    std::shared_ptr<Player> p = this->findPlayerByID(playerID);

    p->setPlayerLevel(level);
}

void Map::updateResourceForTile(const MyRayLib::Vector2D &pos, IResource::resourceType type, int number) {
    int count = 0;
    const int key = pos.getY() * this->_size.getX() + pos.getX();

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

void Map::addEggForTile(const MyRayLib::Vector2D &pos, int id) {
    const int key = pos.getY() * this->_size.getX() + pos.getX();

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

void Map::movePlayer(int playerID, float x, float z, Player::orientationAxis orientation) {
    std::shared_ptr<Player> p = this->findPlayerByID(playerID);

    if (p != nullptr) {
        p->animationWalk();
        p->setRotationAngle((float)orientation);
        p->_movePos = {x, 0.0, z};
    }
}

void Map::deadPlayer(int playerID) {
    std::shared_ptr<Player> p = this->findPlayerByID(playerID);

    if (p != nullptr) {
        p->animationDie();
    }
}

void Map::updatePlayer(float deltaTime) {
    for (auto it = this->_players.begin(); it != this->_players.end();) {
        std::shared_ptr<Player> player = *it;
        player->draw();
        if (player->update(deltaTime) == true) {
            it = this->_players.erase(it);
            continue;
        }
        ++it;
    }
}

void Map::draw() {
    const bool pressed = MyRayLib::Mouse::MyIsMouseButtonPressed(MOUSE_BUTTON_RIGHT);
    bool hit = false;
    for (int y = 0; y < this->_size.getY(); ++y) {
        for (int x = 0; x < this->_size.getX(); ++x) {
            int key = y * this->_size.getX() + x;
            std::shared_ptr<Tile>& tile = this->_map.at(key);

            if (pressed) {
                MyRayLib::Vector3D cubePosition = tile->_cube.getPos();
                MyRayLib::Vector3D cubeSize = {tile->_cube.getWidth(), tile->_cube.getHeight(), tile->_cube.getLength()};
                BoundingBox box = {{ cubePosition.getX() - cubeSize.getX() / 2, cubePosition.getY() - cubeSize.getY() / 2, cubePosition.getZ() - cubeSize.getZ() / 2 },
                                   { cubePosition.getX() + cubeSize.getX() / 2, cubePosition.getY() + cubeSize.getY() / 2, cubePosition.getZ() + cubeSize.getZ() / 2 }};
                if (GetRayCollisionBox(MyRayLib::Mouse::MyGetMouseRay(MyRayLib::Mouse::MyGetMousePosition(), this->_camera.getCamera()), box).hit) {
                    _selectedTileKey = _selectedTileKey == key ? -1 : key;
                    hit = true;
                    this->_link.askTileContent(cubePosition.getX(), cubePosition.getZ());
                }
            }
            tile->draw();
        }
    }
    if (pressed && !hit)
        _selectedTileKey = -1;
    for (int y = 0; y < this->_size.getY(); ++y) {
        for (int x = 0; x < this->_size.getX(); ++x) {
            int key = y * this->_size.getX() + x;
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
