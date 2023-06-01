/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Player.cpp
*/

#include "../../includes/MapHeader/Player.hpp"

using namespace ZappyGui;

Player::Player(int playerNumber, Vector3 position, Vector3 orientation, int playerLevel, const std::string &teamName): _skinModel(MyRayLib::Model("../../assets/garf_marche.iqm")), _skinTexture(MyRayLib::Texture2D("../../assets/T_Garfield_BC.png")), _animation(MyRayLib::AnimationsModel("../../assets/garf_marche.iqm")) {
    this->_playerNumber = playerNumber;
    this->_position = position;
    this->_orientation = orientation;
    this->_playerLevel = playerLevel;
    this->_teamName = teamName;
    this->_skinTexture.MySetMaterialTexture(this->_skinModel.getModel(), MATERIAL_MAP_DIFFUSE);
}

void Player::setDesign(const std::string &modelPath, const std::string &texturePath, const std::string &animationPath) {
    (void)modelPath;
    (void)texturePath;
    (void)animationPath;
}

void Player::move(Vector3 position) {
    this->_position = position;
}

void Player::upgrade(int level) {
    this->_playerLevel = level;
}

void Player::inventory() {}
