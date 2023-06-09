/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Phiras.hpp
*/

#include <string>
#include "../../includes/resources/Phiras.hpp"

using namespace ZappyGui;

Phiras::Phiras(const MyRayLib::Model &model, const MyRayLib::Texture2D &texture, const Vector3 &position):
    _model(model),
    _texture(texture) {
    this->_rotationAngle = 1.0f;
    this->_position = position;
    this->_position.y = 0.08;
    this->_scale  = { 0.2f, 0.2f, 0.2f };
}

Phiras::~Phiras() {}

void Phiras::setPosition(float x, float z) {
    this->_position.x = x;
    this->_position.z = z;
}

const Vector3 &Phiras::getPosition() {
    return this->_position;
}

void Phiras::draw() {
    MyRayLib::Draw::MyDrawModelEx(this->_model.getModel(), this->_position, { 0.0f, 0.0f, 0.0f }, this->_rotationAngle, this->_scale, MyRayLib::MyRayLibColor::White());
}

IResource::resourceType Phiras::getType() {
    return IResource::resourceType::PHIRAS;
}
