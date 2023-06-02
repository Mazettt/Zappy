/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Thystame.hpp
*/

#include <string>
#include "../../includes/resources/Thystame.hpp"

using namespace ZappyGui;

Thystame::Thystame():
    _model(MyRayLib::Model("./assets/Stones/stone_model.obj")),
    _texture(MyRayLib::Texture2D("./assets/Stones/thystame.png")) {
    this->_rotationAngle = 1.0f;
    this->_position = {0.0f, 0.08f, 0.0f};
    this->_scale = { 0.04f, 0.04f, 0.04f };
    this->_texture.MySetMaterialTexture(this->_model.getModel(), MATERIAL_MAP_DIFFUSE);
}

Thystame::~Thystame() {}

void Thystame::setPosition(float x, float z) {
    this->_position.x = x;
    this->_position.z = z;
}

Vector3 Thystame::getPosition() {
    return this->_position;
}

void Thystame::draw() {
    MyRayLib::Draw::MyDrawModelEx(this->_model.getModel(), this->_position, { 0.0f, 0.0f, 0.0f }, this->_rotationAngle, this->_scale, MyRayLib::MyRayLibColor::White());
}
