/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Player.cpp
*/

#include "../../includes/MapHeader/Player.hpp"

using namespace ZappyGui;

Player::Player(const PlayerArguments &playerArgs, MyRayLib::Model &model, const MyRayLib::Texture2D &texture, MyRayLib::AnimationsModel &animation):
    PlayerArguments(playerArgs), _model(model), _texture(texture), _animation(animation), _frameCounterAnimation(0) {
}

void Player::animationWin() {
    this->_animationType = Player::animationPlayerType::PLAYER_WIN;
    this->_frameCounterAnimation = 0;
}

void Player::animationLVLUP() {
    this->_animationType = Player::animationPlayerType::PLAYER_LVLUP;
    this->_frameCounterAnimation = 0;
}

void Player::animationDie() {
    this->_animationType = Player::animationPlayerType::PLAYER_DIE;
    this->_frameCounterAnimation = 0;
}

void Player::animationGet() {
    this->_animationType = Player::animationPlayerType::PLAYER_GET;
    this->_frameCounterAnimation = 0;
}

void Player::animationWait() {
    this->_animationType = Player::animationPlayerType::PLAYER_WAIT;
    this->_frameCounterAnimation = 0;
}

void Player::animationWalk() {
    this->_animationType = Player::animationPlayerType::PLAYER_WALK;
    this->_frameCounterAnimation = 0;
}

void Player::noAnimation() {
    this->_animationType = Player::animationPlayerType::PLAYER_NOTHING;
    this->_frameCounterAnimation = 0;
}

void Player::draw() {
    // this->_animation.MyUpdateModelAnimation(this->_model.getModel(), this->getAnimationType(), this->_frameCounterAnimation);
    MyRayLib::Draw::MyDrawModelEx(this->_model.getModel(), this->getPosition(), this->getOrientationAxis(), this->getRotationAngle(), this->getScale(), MyRayLib::MyRayLibColor::White());
}
