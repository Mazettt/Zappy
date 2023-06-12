/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Player.cpp
*/

#include <algorithm>
#include "../../includes/MapHeader/Player.hpp"

using namespace ZappyGui;

Player::Player(const PlayerArguments &playerArgs, MyRayLib::Model &model, const MyRayLib::Texture2D &texture, MyRayLib::AnimationsModel &animation):
    PlayerArguments(playerArgs), _model(model), _texture(texture), _animation(animation), _frameCounterAnimation(-1), _animationCounter(0) {
    this->setAnimationType(Player::animationPlayerType::PLAYER_WAIT);
}

void Player::addOnInventory(IResource::resourceType type, int quantity) {
    for (std::pair<const IResource::resourceType, int> item : this->_inventory) {
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


const std::unordered_map<IResource::resourceType, int> Player::getInventory() const {
    return this->_inventory;
}

void Player::draw() {
    this->_animation.MyUpdateModelAnimation(this->_model.getModel(), this->getAnimationType(), this->_frameCounterAnimation);
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
