/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** PlayerResource.hpp
*/

#include <string>
#include "../../includes/resources/PlayerResource.hpp"

using namespace ZappyGui;

PlayerResource::PlayerResource():
    _model(MyRayLib::Model("./assets/Stones/stone_model.obj")),
    _texture(MyRayLib::Texture2D("./assets/player.png")) {
    this->_rotationAngle = 1.0f;
    this->_position = {0.0f, 0.08f, 0.0f};
    this->_scale  = { 0.04f, 0.04f, 0.04f };
    this->_texture.MySetMaterialTexture(this->_model.getModel(), MATERIAL_MAP_DIFFUSE);
}

PlayerResource::~PlayerResource() {}

void PlayerResource::setPosition(float x, float z) {
    this->_position.x = x;
    this->_position.z = z;
}

Vector3 PlayerResource::getPosition() {
    return this->_position;
}

void PlayerResource::draw() {
    MyRayLib::Draw::MyDrawModelEx(this->_model.getModel(), this->_position, { 0.0f, 0.0f, 0.0f }, this->_rotationAngle, this->_scale, MyRayLib::MyRayLibColor::White());
}
