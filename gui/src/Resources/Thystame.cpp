/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Thystame.hpp
*/

#include <string>
#include "../../includes/resources/Thystame.hpp"

using namespace ZappyGui;

Thystame::Thystame(const MyRayLib::Model &model, const MyRayLib::Texture2D &texture, const Vector3 &position):
    _model(model),
    _texture(texture) {
    this->_rotationAngle = 1.0f;
    this->_position = position;
    this->_scale = { 0.04f, 0.04f, 0.04f };
}

Thystame::~Thystame() {}

void Thystame::setPosition(float x, float z) {
    this->_position.x = x;
    this->_position.z = z;
}

const Vector3 &Thystame::getPosition() {
    return this->_position;
}

void Thystame::draw() {
    MyRayLib::Draw::MyDrawModelEx(this->_model.getModel(), this->_position, { 0.0f, 0.0f, 0.0f }, this->_rotationAngle, this->_scale, MyRayLib::MyRayLibColor::White());
}

IResource::resourceType Thystame::getType() {
    return IResource::resourceType::THYSTAME;
}
