/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Egg.cpp
*/

#include <string>
#include "../../includes/resources/Egg.hpp"

using namespace ZappyGui;

Egg::Egg(const std::string &modelPath, const std::string &texturePath) {

}

Egg::~Egg() {}

Model Egg::getModel() {
    return this->_model;
}

Texture2D Egg::getTexture() {
    return this->_texture;
}

