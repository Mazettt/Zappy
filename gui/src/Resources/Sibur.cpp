/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Sibur.hpp
*/

#include <string>
#include "../../includes/resources/Sibur.hpp"

using namespace ZappyGui;

Sibur::Sibur(const MyRayLib::Model &model, const MyRayLib::Texture2D &texture, const MyRayLib::Vector3D &position):
    _model(model),
    _texture(texture) {
    this->_rotationAngle = 1.0f;
    this->_position = position;
    this->_position.setY(0.08);
    this->_scale  = { 0.2f, 0.2f, 0.2f };
}

Sibur::~Sibur() {}

void Sibur::setPosition(float x, float z) {
    this->_position.setX(x);
    this->_position.setZ(z);
}

const MyRayLib::Vector3D &Sibur::getPosition() {
    return this->_position;
}

void Sibur::draw() {
    MyRayLib::Draw::MyDrawModelEx(this->_model.getModel(), this->_position.getVector3(), { 0.0f, 0.0f, 0.0f }, this->_rotationAngle, this->_scale.getVector3(), MyRayLib::MyRayLibColor::White());
}

IResource::resourceType Sibur::getType() {
    return IResource::resourceType::SIBUR;
}
