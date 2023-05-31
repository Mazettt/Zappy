/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Cube.cpp
*/

#include "../includes/map/Cube.hpp"

using namespace ZappyGui;

Cube::Cube(Vector3 pos, float width, float height, float length, Color color): _pos(pos), _width(width), _height(height), _length(length), _color(color) {};

Cube::Cube(const Cube& other): _pos(other._pos), _width(other._width), _height(other._height), _length(other._length), _color(other._color) {};

Cube &Cube::operator=(const Cube &cube) {
    if (this != &cube) {
        this->_pos = cube._pos;
        this->_width = cube._width;
        this->_height = cube._height;
        this->_length = cube._length;
        this->_color = cube._color;
    }
    return *this;
}

Vector3 Cube::getPos() const {
    return this->_pos;
}

float Cube::getWidth() const {
    return this->_width;
}

float Cube::getHeight() const {
    return this->_height;
}

float Cube::getLength() const {
    return this->_length;
}

Color Cube::getColor() const {
    return this->_color;
}

Cube::~Cube() {};
