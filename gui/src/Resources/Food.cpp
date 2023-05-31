/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Food.cpp
*/

#include <string>
#include "../../includes/resources/Food.hpp"

using namespace ZappyGui;

Food::Food(const std::string &modelPath, const std::string &texturePath) {
    (void)modelPath;
    (void)texturePath;
}

Food::~Food() {}

Model Food::getModel() {
    return this->_model;
}

Texture2D Food::getTexture() {
    return this->_texture;
}
