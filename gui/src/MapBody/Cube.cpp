    /*
    ** EPITECH PROJECT, 2022
    ** zappy
    ** File description:
    ** Cube.cpp
    */

    #include "../../includes/MapHeader/Cube.hpp"

    using namespace ZappyGui;

    Cube::Cube(MyRayLib::Vector3D pos, float width, float height, float length, Color color): _pos(pos), _width(width), _height(height), _length(length), _color(color) {};

    Cube::Cube(const Cube &other): _pos(other._pos), _width(other._width), _height(other._height), _length(other._length), _color(other._color) {};

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

    MyRayLib::Vector3D Cube::getPos() const {
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

    void Cube::draw() {
        MyRayLib::Draw::MyDrawCubeWires(this->_pos.getVector3(), this->_width, this->_height, this->_length, GRAY);
        MyRayLib::Draw::MyDrawCube(this->_pos.getVector3(), this->_width, this->_height, this->_length, this->_color);
    }

    Cube::~Cube() {};
