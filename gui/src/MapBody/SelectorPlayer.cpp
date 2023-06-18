/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** SelectorPlayer.cpp
*/

#include "../../includes/MapHeader/SelectorPlayer.hpp"

using namespace ZappyGui;

SelectorPlayer::SelectorPlayer(MyRayLib::Model &model, MyRayLib::AnimationsModel &animation): _model(model), _animation(animation) {
    this->_frameCounterAnimation = -1;
    this->_pos = {0.0, 0.0, 0.0};
}

void SelectorPlayer::setPosition(const MyRayLib::Vector3D &pos) {
    this->_pos = pos;
    this->_pos.setY(this->_pos.getY() + 0.85);
}

const MyRayLib::Vector3D SelectorPlayer::getPosition() const {
    return this->_pos;
}

void SelectorPlayer::update() {
    this->_animation.MyUpdateModelAnimation(this->_model.getModel(), 0, this->_frameCounterAnimation);
}

void SelectorPlayer::draw() {
    MyRayLib::Draw::MyDrawModelEx(this->_model.getModel(), this->getPosition().getVector3(), {1.0, 0.0, 0.0}, -90.0, {0.01, 0.01, 0.01}, MyRayLib::MyRayLibColor::White());
}
