/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Pizza.cpp
*/

#include <string>
#include "../../includes/resources/Pizza.hpp"

using namespace ZappyGui;

Pizza::Pizza(const MyRayLib::Model &model, const MyRayLib::Texture2D &texture, const Vector3 &position):
    _model(model),
    _texture(texture) {
    this->_rotationAngle = 1.0f;
    this->_position = position;
    this->_scale  = { 0.01f, 0.01f, 0.01f };
}

Pizza::~Pizza() {}

void Pizza::setPosition(float x, float z) {
    this->_position.x = x;
    this->_position.z = z;
}

const Vector3 &Pizza::getPosition() {
    return this->_position;
}

void Pizza::draw() {
    MyRayLib::Draw::MyDrawModelEx(this->_model.getModel(), this->_position, { 0.0f, 0.0f, 0.0f }, this->_rotationAngle, this->_scale, MyRayLib::MyRayLibColor::White());
}

IResource::resourceType Pizza::getType() {
    return IResource::resourceType::PIZZA;
}
