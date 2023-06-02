/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Phiras.hpp
*/

#include <string>
#include "../../includes/resources/Phiras.hpp"

using namespace ZappyGui;

Phiras::Phiras():
    _model(MyRayLib::Model("./assets/Stones/stone_model.obj")),
    _texture(MyRayLib::Texture2D("./assets/Stones/phiras.png")) {
    this->_rotationAngle = 1.0f;
    this->_position = {0.0f, 0.08f, 0.0f};
    this->_scale = { 0.04f, 0.04f, 0.04f };
    this->_texture.MySetMaterialTexture(this->_model.getModel(), MATERIAL_MAP_DIFFUSE);
}

Phiras::~Phiras() {}

void Phiras::setPosition(float x, float z) {
    this->_position.x = x;
    this->_position.z = z;
}

Vector3 Phiras::getPosition() {
    return this->_position;
}

void Phiras::draw() {
    MyRayLib::Draw::MyDrawModelEx(this->_model.getModel(), this->_position, { 0.0f, 0.0f, 0.0f }, this->_rotationAngle, this->_scale, MyRayLib::MyRayLibColor::White());
}
