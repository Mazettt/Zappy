/*
** EPITECH PROJECT, 2022
** gui
** File description:
** map.cpp
*/

#include "../../includes/MapHeader/Map.hpp"

using namespace ZappyGui;

Map::Map(int x, int y, ResourceManager &manager): _manager(manager), _music("./assets/GarfieldCoolCat.mp3") {
    float widthCube = 1.0;
    float lengthCube = 1.0;
    float heightCube = 0.1;
    this->_size.x = x;
    this->_size.y = y;
    this->_map.resize(x * y);
    _manager.initialize();

    if (this->_music.MyIsMusicReady())
        this->_music.MyPlayMusic();

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

    PlayerArguments playerArgs(0, "Team1", {3.0f, 0.0f, 8.0f}, {0.0f, 1.0f, 0.0f}, 0.0f, {0.6f, 0.6f, 0.6f}, 0 , 3);
    this->addPlayerForTile(playerArgs);
    PlayerArguments playerArgs1(1, "Team1", {5.0f, 0.0f, 7.0f}, {0.0f, 1.0f, 0.0f}, 90.0f, {0.6f, 0.6f, 0.6f}, 0 , 1);
    this->addPlayerForTile(playerArgs1);
    PlayerArguments playerArgs2(2, "Team1", {8.0f, 0.0f, 3.0f}, {0.0f, 1.0f, 0.0f}, 180.0f, {0.6f, 0.6f, 0.6f}, 0 , 3);
    this->addPlayerForTile(playerArgs2);
    PlayerArguments playerArgs3(3, "Team1", {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, 270.0f, {0.6f, 0.6f, 0.6f}, 0 , 1);
    this->addPlayerForTile(playerArgs3);
}

std::shared_ptr<Player> Map::findPlayerByID(int id) {
    for (std::shared_ptr<Player> p : this->_players) {
        if (p->getPlayerNumber() == id) {
            return p;
        }
    }
    return nullptr;
}

bool Map::setPlayerLevel(int playerID, int level) {
    std::shared_ptr<Player> p = this->findPlayerByID(playerID);

    p->setPlayerLevel(level);
}

void Map::addResourceForTile(const Vector2 &pos, IResource::resourceType type) {
    this->_map[pos.y * this->_size.x + pos.x]->addResource(this->_manager, type);
}

void Map::addPlayerForTile(const PlayerArguments &playerArgs) {
    auto &modelPlayer = this->_manager.getPlayerModel();
    auto &texture = this->_manager.getTexture(IResource::resourceType::PLAYER);
    auto &animation = this->_manager.getAnimation(IResource::resourceType::PLAYER);
    this->_players.push_back(std::make_shared<Player>(playerArgs, modelPlayer, texture, animation));
}

bool Map::movePlayer(int playerID, float x, float z) {
    std::shared_ptr<Player> p = this->findPlayerByID(playerID);

    if (p != nullptr) {
        Vector3 pos = p->getPosition();
        p->_movePos = {x - pos.x, 0.0, z - pos.z};
        // TODO orientation
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
    for (int y = 0; y < this->_size.y; ++y) {
        for (int x = 0; x < this->_size.x; ++x) {
            int key = y * this->_size.x + x;
            std::shared_ptr<Tile> &tile = this->_map.at(key);
            tile->draw();
        }
    }

    float moveSpeed = 0.06;

    for (auto it = this->_players.begin(); it != this->_players.end();) {
        std::shared_ptr<Player> p = *it;
        Vector3 pos = p->getPosition();
        if (p->_movePos.x > 0.0) {
            p->setPosition({ pos.x += moveSpeed, 0.0, pos.z });
            p->_movePos.x -= moveSpeed;
        }
        if (p->_movePos.z > 0.0) {
            p->setPosition({ pos.x, 0.0, pos.z += moveSpeed });
            p->_movePos.z -= moveSpeed;
        }
        if (p->_movePos.x < 0.0) {
            p->setPosition({ pos.x -= moveSpeed, 0.0, pos.z });
            p->_movePos.x += moveSpeed;
        }
        if (p->_movePos.z < 0.0) {
            p->setPosition({ pos.x, 0.0, pos.z -= moveSpeed });
            p->_movePos.z += moveSpeed;
        }
        float epsilon = 0.0001f;
        if (abs(p->_movePos.x) < epsilon && abs(p->_movePos.z) < epsilon) {
            if (p->getAnimationType() == Player::animationPlayerType::PLAYER_WALK) {
                p->animationWait();
            }
            if (p->_animationCounter > 0) {
                p->_animationCounter -= 1;
            } else if (p->_animationCounter <= 0) {
                if (p->getAnimationType() == Player::animationPlayerType::PLAYER_DIE) {
                    this->_players.erase(it);
                    continue;
                } else {
                    p->setAnimationType(Player::animationPlayerType::PLAYER_WAIT);
                }
            }
        }
        p->draw();
        ++it;
    }
}

Map::~Map() {}

void Map::updateMusic() {
    this->_music.MySetMusicVolume(this->_volumeMusicGame);
    this->_music.MyUpdateMusic();
}
