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

void Player::move(float deltaTime) { //TODO
    float moveSpeed = 0.06;
    // Vector3 currentPos = this->getPosition();
    float currentX = this->getPosition().x;
    float currentY = this->getPosition().y;
    float currentZ = this->getPosition().z;
    float orientation = this->getRotationAngle();

    if ((this->_movePos.x == currentX) && (this->_movePos.y == currentY) && (this->_movePos.z == currentZ))
        return;
    if ((orientationAxis::SOUTH == orientation) && (std::round(currentZ) == 9))
        this->setPosition({ currentX, 0.0, 0.0});
    else if ((orientationAxis::NORTH == orientation) && (std::round(currentZ) == 0))
        this->setPosition({ currentX, 0.0, 9.0});
    else if ((orientationAxis::EAST == orientation) && (std::round(currentZ) == 9))
        this->setPosition({ 0.0, 0.0, currentZ});
    else if ((orientationAxis::WEST == orientation) && (std::round(currentZ) == 0))
        this->setPosition({ 9.0, 0.0, currentZ});
    else
        this->setPosition(this->_movePos);


    // float moveX = 0.0f;
    // float moveZ = 0.0f;

    // if (this->_movePos.x > 0.0f) {
    //     moveX = std::min(moveSpeed, this->_movePos.x);
    //     this->_movePos.x -= moveX;
    // } else if (this->_movePos.x < 0.0f) {
    //     moveX = std::max(-moveSpeed, this->_movePos.x);
    //     this->_movePos.x -= moveX;
    // }
    // if (this->_movePos.z > 0.0f) {
    //     moveZ = std::min(moveSpeed, this->_movePos.z);
    //     this->_movePos.z -= moveZ;
    // } else if (this->_movePos.z < 0.0f) {
    //     moveZ = std::max(-moveSpeed, this->_movePos.z);
    //     this->_movePos.z -= moveZ;
    // }
    // pos.x += moveX;
    // pos.z += moveZ;
    // this->setPosition(pos);
}

bool Player::updateAnimation(float deltaTime) { //TODO
    float epsilon = 0.0001f;

    if (std::abs(this->_movePos.x) < epsilon && std::abs(this->_movePos.z) < epsilon) {
        if (this->getAnimationType() == Player::animationPlayerType::PLAYER_WALK) {
            this->animationWait();
        }
        if (this->_animationCounter > 0) {
            this->_animationCounter -= 1;
        } else if (this->_animationCounter <= 0) {
            if (this->getAnimationType() == Player::animationPlayerType::PLAYER_DIE) {
                return true;
            } else {
                this->setAnimationType(Player::animationPlayerType::PLAYER_WAIT);
            }
        }
    }
    this->_animation.MyUpdateModelAnimation(this->_model.getModel(), this->getAnimationType(), this->_frameCounterAnimation);
    return false;
}

bool Player::update(float deltaTime) {
    this->move(deltaTime);
    return this->updateAnimation(deltaTime);
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
