/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Deraumere.hpp
*/

#include <string>
#include "../../includes/resources/Deraumere.hpp"

using namespace ZappyGui;

Deraumere::Deraumere():
    _model(MyRayLib::Model("./assets/Stones/stone_model.obj")),
    _texture(MyRayLib::Texture2D("./assets/Stones/deraumere.png")) {
    this->_rotationAngle = 1.0f;
    this->_position = {0.0f, 0.8f, 0.0f};
    this->_scale  = { 0.06f, 0.06f, 0.06f };
    this->_texture.MySetMaterialTexture(this->_model.getModel(), MATERIAL_MAP_DIFFUSE);
}

Deraumere::~Deraumere() {}

void Deraumere::setPosition(int x, int z) {
    this->_position.x = x;
    this->_position.z = z;
}

void Deraumere::draw() {
    MyRayLib::Draw::MyDrawModelEx(this->_model.getModel(), this->_position, { 0.0f, 0.0f, 0.0f }, this->_rotationAngle, this->_scale, MyRayLib::MyRayLibColor::White());
}
