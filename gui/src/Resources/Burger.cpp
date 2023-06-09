/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Burger.cpp
*/

#include <string>
#include "../../includes/resources/Burger.hpp"

using namespace ZappyGui;

Burger::Burger(const MyRayLib::Model &model, const MyRayLib::Texture2D &texture, const Vector3 &position):
    _model(model),
    _texture(texture) {
    this->_rotationAngle = 1.0f;
    this->_position = position;
    this->_scale  = { 0.6f, 0.6f, 0.6f };
}

Burger::~Burger() {}

void Burger::setPosition(float x, float z) {
    this->_position.x = x;
    this->_position.z = z;
}

const Vector3 &Burger::getPosition() {
    return this->_position;
}

void Burger::draw() {
    MyRayLib::Draw::MyDrawModelEx(this->_model.getModel(), this->_position, { 0.0f, 0.0f, 0.0f }, this->_rotationAngle, this->_scale, MyRayLib::MyRayLibColor::White());
}

IResource::resourceType Burger::getType() {
    return IResource::resourceType::BURGER;
}
