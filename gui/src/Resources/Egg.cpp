/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Egg.cpp
*/

#include <string>
#include "../../includes/resources/Egg.hpp"

using namespace ZappyGui;

Egg::Egg(const MyRayLib::Model &model, const MyRayLib::Texture2D &texture, const MyRayLib::Vector3D &position, int id):
    _model(model),
    _texture(texture),
    _id(id) {
    this->_rotationAngle = 1.0f;
    this->_position = position;
    this->_position.setY(0.076);
    this->_scale  = { 0.2f, 0.2f, 0.2f };
}

Egg::~Egg() {}

void Egg::setPosition(float x, float z) {
    this->_position.setX(x);
    this->_position.setZ(z);
}

const MyRayLib::Vector3D &Egg::getPosition() {
    return this->_position;
}

void Egg::draw() {
    MyRayLib::Draw::MyDrawModelEx(this->_model.getModel(), this->_position.getVector3(), { 0.0f, 0.0f, 0.0f }, this->_rotationAngle, this->_scale.getVector3(), MyRayLib::MyRayLibColor::White());
}

IResource::resourceType Egg::getType() {
    return IResource::resourceType::EGG;
}
