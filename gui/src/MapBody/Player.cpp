/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Player.cpp
*/

#include <algorithm>
#include "../../includes/MapHeader/Player.hpp"
#include <cmath>

using namespace ZappyGui;

Player::Player(const PlayerArguments &playerArgs, MyRayLib::Model &model, const MyRayLib::Texture2D &texture, MyRayLib::AnimationsModel &animation):
    PlayerArguments(playerArgs),
    _model(model),
    _texture(texture),
    _frameCounterAnimation(-1),
    _animation(animation),
    _animationCounter(0)
{
    this->_movePos = { 0.0f, 0.0f, 0.0f };
    this->setAnimationType(Player::animationPlayerType::PLAYER_WAIT);
    this->setInventory(0, 0, 0, 0, 0, 0, 0);
}

void Player::addOnInventory(IResource::resourceType type, int quantity) {
    for (std::pair<const IResource::resourceType, int> &item : this->_inventory) {
        if (item.first == type) {
            item.second += quantity;
            return;
        }
    }
    this->_inventory.insert({ type, quantity });
}

bool Player::removeOnInventory(IResource::resourceType type, int quantity) {
    auto it = std::find_if(this->_inventory.begin(), this->_inventory.end(),
        [type](const auto& item) {
            return item.first == type;
        }
    );
    if (it != this->_inventory.end()) {
        if (it->second < 1) {
            this->_inventory.erase(it);
        } else {
            it->second -= quantity;
        }
        return true;
    }
    return false;
}

Vector3 Player::move(float deltaTime) {
    float moveSpeed = (1 * 1) * deltaTime;
    Vector3 currentPos = this->getPosition();
    float currentX = currentPos.x;
    float currentY = currentPos.y;
    float currentZ = currentPos.z;
    float orientation = this->getRotationAngle();
    Vector3 newPos;

    if ((orientationAxis::SOUTH == orientation)) {
        newPos = { currentX, 0.0, currentZ + moveSpeed};
        if (newPos.z > this->_movePos.z)
            newPos.z = this->_movePos.z;
    } else if ((orientationAxis::NORTH == orientation)) {
        newPos = { currentX, 0.0, currentZ - moveSpeed};
        if (newPos.z < this->_movePos.z)
            newPos.z = this->_movePos.z;
    } else if ((orientationAxis::EAST == orientation)) {
        newPos = { currentX + moveSpeed, 0.0, currentZ};
        if (newPos.x > this->_movePos.x)
            newPos.x = this->_movePos.x;
    } else if ((orientationAxis::WEST == orientation)) {
        newPos = { currentX - moveSpeed, 0.0, currentZ};
        if (newPos.x < this->_movePos.x)
            newPos.x = this->_movePos.x;
    }
    this->setPosition(newPos);
    return newPos;
}

bool Player::updateAnimation(Vector3 newPos, float deltaTime) {
    if (this->getAnimationType() == animationPlayerType::PLAYER_WALK
        && newPos.x == this->_movePos.x && newPos.z == this->_movePos.z) {
        this->animationWait();
    }
    if (this->_frameCounterAnimation >= 48) {
        if (this->getAnimationType() == animationPlayerType::PLAYER_GET) {
            this->animationWait();
        }
        if (this->getAnimationType() == animationPlayerType::PLAYER_DIE) {
            return true;
        }
    }
    this->_animation.MyUpdateModelAnimation(this->_model.getModel(), this->getAnimationType(), this->_frameCounterAnimation);
    return false;
}

bool Player::update(float deltaTime) {
    Vector3 newPos = this->move(deltaTime);
    return this->updateAnimation(newPos, deltaTime);
}

const std::unordered_map<IResource::resourceType, int> &Player::getInventory() const {
    return this->_inventory;
}

void Player::draw() {
    MyRayLib::Draw::MyDrawModelEx(this->_model.getModel(), this->getPosition(), this->getOrientationAxis(), this->getRotationAngle(), this->getScale(), MyRayLib::MyRayLibColor::White());
}

void Player::animationWin() {
    this->setAnimationType(Player::animationPlayerType::PLAYER_WIN);
    this->_frameCounterAnimation = 0;
}

void Player::animationLVLUP() {
    this->setAnimationType(Player::animationPlayerType::PLAYER_LVLUP);
    this->_frameCounterAnimation = 0;
}

void Player::animationDie() {
    this->setAnimationType(Player::animationPlayerType::PLAYER_DIE);
    this->_frameCounterAnimation = 0;
    this->_animationCounter = 30;
}

void Player::animationGet() {
    this->setAnimationType(Player::animationPlayerType::PLAYER_GET);
    this->_frameCounterAnimation = 0;
}

void Player::animationWait() {
    this->setAnimationType(Player::animationPlayerType::PLAYER_WAIT);
    this->_frameCounterAnimation = 0;
}

void Player::animationWalk() {
    this->setAnimationType(Player::animationPlayerType::PLAYER_WALK);
    // this->_frameCounterAnimation = 0;
}

void Player::noAnimation() {
    this->setAnimationType(Player::animationPlayerType::PLAYER_NOTHING);
    this->_frameCounterAnimation = 0;
}

void Player::setInventory(int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame)
{
    this->_inventory[IResource::resourceType::BURGER] = food;
    this->_inventory[IResource::resourceType::LINEMATE] = linemate;
    this->_inventory[IResource::resourceType::DERAUMERE] = deraumere;
    this->_inventory[IResource::resourceType::SIBUR] = sibur;
    this->_inventory[IResource::resourceType::MENDIANE] = mendiane;
    this->_inventory[IResource::resourceType::PHIRAS] = phiras;
    this->_inventory[IResource::resourceType::THYSTAME] = thystame;
}
