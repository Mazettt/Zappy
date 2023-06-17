/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Burger.cpp
*/

#include <string>
#include "../../includes/resources/Burger.hpp"

using namespace ZappyGui;

Burger::Burger(const MyRayLib::Model &model, const MyRayLib::Texture2D &texture, const MyRayLib::Vector3D &position):
    _model(model),
    _texture(texture) {
    this->_rotationAngle = 1.0f;
    this->_position = position;
    this->_position.setY(0.05);
    this->_scale = { 0.54f, 0.54f, 0.54f };
}

Burger::~Burger() {}

void Burger::setPosition(float x, float z) {
    this->_position.setX(x);
    this->_position.setZ(z);
}

const MyRayLib::Vector3D &Burger::getPosition() {
    return this->_position;
}

void Burger::draw() {
    MyRayLib::Draw::MyDrawModelEx(this->_model.getModel(), this->_position.getVector3(), { 0.0f, 0.0f, 0.0f }, this->_rotationAngle, this->_scale.getVector3(), MyRayLib::MyRayLibColor::White());
}

IResource::resourceType Burger::getType() {
    return IResource::resourceType::BURGER;
}
