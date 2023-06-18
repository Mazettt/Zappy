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
    _animation(animation)
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

MyRayLib::Vector3D Player::move(float deltaTime) {
    float moveSpeed = (1 * 1) * deltaTime;
    MyRayLib::Vector3D currentPos = this->getPosition();
    float orientation = this->getRotationAngle();
    MyRayLib::Vector3D newPos;

    if ((float)orientationAxis::SOUTH == orientation) {
        newPos = { currentPos.getX(), 0.0, currentPos.getZ() + moveSpeed};
        if (newPos.getZ() > this->_movePos.getZ())
            newPos.setZ(this->_movePos.getZ());
    } else if ((float)orientationAxis::NORTH == orientation) {
        newPos = { currentPos.getX(), 0.0, currentPos.getZ() - moveSpeed};
        if (newPos.getZ() < this->_movePos.getZ())
            newPos.setZ(this->_movePos.getZ());
    } else if ((float)orientationAxis::EAST == orientation) {
        newPos = { currentPos.getX() + moveSpeed, 0.0, currentPos.getZ()};
        if (newPos.getX() > this->_movePos.getX())
            newPos.setX(this->_movePos.getX());
    } else if ((float)orientationAxis::WEST == orientation) {
        newPos = { currentPos.getX() - moveSpeed, 0.0, currentPos.getZ()};
        if (newPos.getX() < this->_movePos.getX())
            newPos.setX(this->_movePos.getX());
    }
    this->setPosition(newPos);
    return newPos;
}

bool Player::updateAnimation(MyRayLib::Vector3D newPos, float deltaTime) {
    if (newPos.getX() == this->_movePos.getX() && newPos.getZ() == this->_movePos.getZ()) {
        this->animationWait();
    } else {
        if (this->getAnimationType() != animationPlayerType::PLAYER_WALK) {
            this->animationWalk();
        }
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
    MyRayLib::Vector3D newPos = this->move(deltaTime);
    return this->updateAnimation(newPos, deltaTime);
}

const std::unordered_map<IResource::resourceType, int> &Player::getInventory() const {
    return this->_inventory;
}

void Player::draw() {
    MyRayLib::Draw::MyDrawModelEx(this->_model.getModel(), this->getPosition().getVector3(), this->getOrientationAxis().getVector3(), this->getRotationAngle(), this->getScale().getVector3(), MyRayLib::MyRayLibColor::White());
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
    this->_frameCounterAnimation = 0;
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
