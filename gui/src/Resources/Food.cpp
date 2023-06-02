/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Food.cpp
*/

#include <string>
#include "../../includes/resources/Food.hpp"

using namespace ZappyGui;

Food::Food():
    _model(MyRayLib::Model("./assets/Food/pizza.obj")),
    _texture(MyRayLib::Texture2D("./assets/Food/pizza.png")) {
    this->_rotationAngle = 1.0f;
    this->_position = {0.0f, 0.8f, 0.0f};
    this->_scale  = { 0.01f, 0.01f, 0.01f };
    this->_texture.MySetMaterialTexture(this->_model.getModel(), MATERIAL_MAP_DIFFUSE);
}

Food::~Food() {}

void Food::setPosition(float x, float z) {
    this->_position.x = x;
    this->_position.z = z;
}

Vector3 Food::getPosition() {
    return this->_position;
}

void Food::draw() {
    MyRayLib::Draw::MyDrawModelEx(this->_model.getModel(), this->_position, { 0.0f, 0.0f, 0.0f }, this->_rotationAngle, this->_scale, MyRayLib::MyRayLibColor::White());
}
