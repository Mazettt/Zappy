/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Egg.cpp
*/

#include <string>
#include "../../includes/resources/Egg.hpp"

using namespace ZappyGui;

Egg::Egg(const MyRayLib::Model &model, const MyRayLib::Texture2D &texture, const Vector3 &position):
    _model(model),
    _texture(texture) {
    this->_rotationAngle = 1.0f;
    this->_position = position;
    this->_position.y = 0.076;
    this->_scale  = { 0.2f, 0.2f, 0.2f };
}

Egg::~Egg() {}

void Egg::setPosition(float x, float z) {
    this->_position.x = x;
    this->_position.z = z;
}

const Vector3 &Egg::getPosition() {
    return this->_position;
}

void Egg::draw() {
    MyRayLib::Draw::MyDrawModelEx(this->_model.getModel(), this->_position, { 0.0f, 0.0f, 0.0f }, this->_rotationAngle, this->_scale, MyRayLib::MyRayLibColor::White());
}

IResource::resourceType Egg::getType() {
    return IResource::resourceType::EGG;
}
