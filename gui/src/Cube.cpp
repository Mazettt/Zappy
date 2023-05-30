/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Cube.cpp
*/

#include "../includes/Cube.hpp"

using namespace ZappyGui;

Cube::Cube(Vector3 pos, float width, float height, float length, Color color): _pos(pos), _width(width), _height(height), _length(length), _color(color) {};

const Vector3 Cube::getPos() const {
    return this->_pos;
}

const float Cube::getWidth() const {
    return this->_width;
}

const float Cube::getHeight() const {
    return this->_height;
}

const float Cube::getLength() const {
    return this->_length;
}

const Color Cube::getColor() const {
    return this->_color;
}

Cube::~Cube() {};
