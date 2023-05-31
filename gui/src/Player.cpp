/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Player.cpp
*/

#include "../includes/map/Player.hpp"

using namespace ZappyGui;

Player::Player(int playerNumber, Vector2 position, Vector3 orientation, int playerLevel, const std::string &teamName) {
    this->_playerNumber = playerNumber;
    this->_position = position;
    this->_orientation = orientation;
    this->_playerLevel = playerLevel;
    this->_teamName = teamName;
}

void Player::setDesign(const std::string &modelPath, const std::string &texturePath, const std::string &animationPath) {
    (void)modelPath;
    (void)texturePath;
    (void)animationPath;
}

void Player::move(Vector2 position) {
    this->_position = position;
}

void Player::upgrade(int level) {
    this->_playerLevel = level;
}

void Player::inventory() {

}
