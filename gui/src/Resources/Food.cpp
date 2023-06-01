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
    _model(MyRayLib::Model("./assets/Stones/rock.fbx")),
    _texture(MyRayLib::Texture2D("./assets/Stones/texture.png")) {
    this->_orientationAxis = { 0.0f, 1.0f, 0.0f };
    this->_rotationAngle = -90.0;
    this->_scale = {1.0f, 1.0f, 1.0f};
    this->_position = {0.0f, 0.0f, 0.0f};
}

Food::~Food() {}

void Food::setPosition(int x, int z) {
    this->_position.x = x;
    this->_position.z = z;
}

void Food::draw() {
    MyRayLib::Draw::MyDrawModel(this->_model.getModel(), this->_position, this->_rotationAngle, MyRayLib::MyRayLibColor::White());
}
