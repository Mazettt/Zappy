/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Player.cpp
*/

#include "../../includes/MapHeader/Player.hpp"

using namespace ZappyGui;

Player::Player(const PlayerArguments &playerArgs, MyRayLib::Model &model, const MyRayLib::Texture2D &texture, MyRayLib::AnimationsModel &animation):
    PlayerArguments(playerArgs), _model(model), _texture(texture), _animation(animation) {
}

void Player::draw() {
    this->_animation.MyUpdateModelAnimation(this->_model.getModel(), this->getAnimationType());
    MyRayLib::Draw::MyDrawModelEx(this->_model.getModel(), this->getPosition(), this->getOrientationAxis(), this->getRotationAngle(), this->getScale(), MyRayLib::MyRayLibColor::White());
}
