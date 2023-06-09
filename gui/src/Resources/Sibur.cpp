/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Sibur.hpp
*/

#include <string>
#include "../../includes/resources/Sibur.hpp"

using namespace ZappyGui;

Sibur::Sibur(const MyRayLib::Model &model, const MyRayLib::Texture2D &texture, const Vector3 &position):
    _model(model),
    _texture(texture) {
    this->_rotationAngle = 1.0f;
    this->_position = position;
    this->_position.y = 0.08;
    this->_scale  = { 0.2f, 0.2f, 0.2f };
}

Sibur::~Sibur() {}

void Sibur::setPosition(float x, float z) {
    this->_position.x = x;
    this->_position.z = z;
}

const Vector3 &Sibur::getPosition() {
    return this->_position;
}

void Sibur::draw() {
    MyRayLib::Draw::MyDrawModelEx(this->_model.getModel(), this->_position, { 0.0f, 0.0f, 0.0f }, this->_rotationAngle, this->_scale, MyRayLib::MyRayLibColor::White());
}

IResource::resourceType Sibur::getType() {
    return IResource::resourceType::SIBUR;
}
