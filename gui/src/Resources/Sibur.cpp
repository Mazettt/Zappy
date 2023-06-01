/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Sibur.hpp
*/

#include <string>
#include "../../includes/resources/Sibur.hpp"

using namespace ZappyGui;

Sibur::Sibur():
    _model(MyRayLib::Model("./assets/Stones/stone_model.obj")),
    _texture(MyRayLib::Texture2D("./assets/Stones/sibur.png")) {
    this->_rotationAngle = 1.0f;
    this->_position = {0.0f, 0.8f, 0.0f};
    this->_scale  = { 0.06f, 0.06f, 0.06f };
    this->_texture.MySetMaterialTexture(this->_model.getModel(), MATERIAL_MAP_DIFFUSE);
}

Sibur::~Sibur() {}

void Sibur::setPosition(int x, int z) {
    this->_position.x = x;
    this->_position.z = z;
}

void Sibur::draw() {
    MyRayLib::Draw::MyDrawModelEx(this->_model.getModel(), this->_position, { 0.0f, 0.0f, 0.0f }, this->_rotationAngle, this->_scale, MyRayLib::MyRayLibColor::White());
}
