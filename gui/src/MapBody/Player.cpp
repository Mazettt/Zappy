/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Player.cpp
*/

#include "../../includes/MapHeader/Player.hpp"

using namespace ZappyGui;

Player::Player(int playerNumber, int playerLevel, const std::string &teamName, Vector3 position, Vector3 orientationAxis, float rotationAngle, Vector3 scale):
    _skinModel(MyRayLib::Model("./assets/thegarf.iqm")),
    _skinTexture(MyRayLib::Texture2D("./assets/T_Garfield_BC.png")),
    _animation(MyRayLib::AnimationsModel("./assets/thegarf.iqm")) {
    this->_playerNumber = playerNumber;
    this->_position = position;
    this->_orientationAxis = orientationAxis;
    this->_rotationAngle = rotationAngle;
    this->_scale = scale;
    this->_playerLevel = playerLevel;
    this->_teamName = teamName;
    this->_skinTexture.MySetMaterialTexture(this->_skinModel.getModel(), MATERIAL_MAP_DIFFUSE);
}

void Player::move(Vector3 position) {
    this->_position = position;
}

void Player::upgrade(int level) {
    this->_playerLevel = level;
}

void Player::draw() {
    this->_animation.MyUpdateModelAnimation(this->_skinModel.getModel(), 0);
    MyRayLib::Draw::MyDrawModelEx(this->_skinModel.getModel(), this->_position, this->_orientationAxis, this->_rotationAngle, this->_scale, MyRayLib::MyRayLibColor::White());
}

void Player::inventory() {}
