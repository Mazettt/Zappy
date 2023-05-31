/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Cube.hpp
*/
#pragma once
#include "raylib.h"

namespace ZappyGui {
    class Cube {
        private:
            Vector3 _pos;
            float _width;
            float _height;
            float _length;
            Color _color;

        public:
            Cube(Vector3 pos, float width, float height, float length, Color color);
            Cube(const Cube& other);
            Cube &operator=(const Cube &cube);
            Vector3 getPos() const;
            float getWidth() const;
            float getHeight() const;
            float getLength() const;
            Color getColor() const;
            ~Cube();
    };
}
