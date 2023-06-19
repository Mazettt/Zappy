/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Broadcast.cpp
*/

#include <string>
#include "../../includes/resources/Broadcast.hpp"

using namespace ZappyGui;

Broadcast::Broadcast(const MyRayLib::Model &model, const MyRayLib::Texture2D &texture, const MyRayLib::Vector3D &position, int targetPlayerId):
    _model(model),
    _texture(texture),
    _targetPlayerId(targetPlayerId) {
    this->_rotationAngle = 1.0f;
    this->_position = position;
    this->_position.setY(this->_position.getY() + 0.6f);
    this->_scale = { 0.08f, 0.08f, 0.08f };
}

Broadcast::~Broadcast() {}

void Broadcast::setPosition(float x, float z) {
    this->_position.setX(x);
    this->_position.setZ(z);
}

const MyRayLib::Vector3D &Broadcast::getPosition() {
    return this->_position;
}

void Broadcast::draw() {
    MyRayLib::Draw::MyDrawModelEx(this->_model.getModel(), this->_position.getVector3(), { 0.0f, 0.0f, 0.0f }, this->_rotationAngle, this->_scale.getVector3(), MyRayLib::MyRayLibColor::White());
}

IResource::resourceType Broadcast::getType() {
    return IResource::resourceType::BROADCAST;
}
