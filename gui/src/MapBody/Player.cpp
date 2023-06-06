/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Player.cpp
*/

#include "../../includes/MapHeader/Player.hpp"

using namespace ZappyGui;

Player::Player(const PlayerArguments &playerArgs, const MyRayLib::Model &model, const MyRayLib::Texture2D &texture):
    PlayerArguments(playerArgs), _model(model), _texture(texture) {
}

void Player::draw() {
    MyRayLib::Draw::MyDrawModelEx(this->_model.getModel(), this->getPosition(), this->getOrientationAxis(), this->getRotationAngle(), this->getScale(), MyRayLib::MyRayLibColor::White());
}
