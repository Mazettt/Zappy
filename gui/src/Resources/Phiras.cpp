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
    this->_position = {0.0f, 0.8f, 0.0f};
    this->_scale  = { 0.06f, 0.06f, 0.06f };
    this->_texture.MySetMaterialTexture(this->_model.getModel(), MATERIAL_MAP_DIFFUSE);
}

Phiras::~Phiras() {}

void Phiras::setPosition(int x, int z) {
    this->_position.x = x;
    this->_position.z = z;
}

void Phiras::draw() {
    MyRayLib::Draw::MyDrawModelEx(this->_model.getModel(), this->_position, { 0.0f, 0.0f, 0.0f }, this->_rotationAngle, this->_scale, MyRayLib::MyRayLibColor::White());
}
