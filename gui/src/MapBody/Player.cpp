/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Player.cpp
*/

#include <algorithm>
#include "../../includes/MapHeader/Player.hpp"

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

void Player::move() {
    float moveSpeed = 0.06;
    Vector3 pos = this->getPosition();
    float moveX = 0.0f;
    float moveZ = 0.0f;

    if (this->_movePos.x > 0.0f) {
        moveX = std::min(moveSpeed, this->_movePos.x);
        this->_movePos.x -= moveX;
    } else if (this->_movePos.x < 0.0f) {
        moveX = std::max(-moveSpeed, this->_movePos.x);
        this->_movePos.x -= moveX;
    }
    if (this->_movePos.z > 0.0f) {
        moveZ = std::min(moveSpeed, this->_movePos.z);
        this->_movePos.z -= moveZ;
    } else if (this->_movePos.z < 0.0f) {
        moveZ = std::max(-moveSpeed, this->_movePos.z);
        this->_movePos.z -= moveZ;
    }
    pos.x += moveX;
    pos.z += moveZ;
    this->setPosition(pos);
}

bool Player::updateAnimation() {
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

bool Player::update() {
    this->move();
    return this->updateAnimation();
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
