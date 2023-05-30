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
            const Vector3 getPos() const;
            const float getWidth() const;
            const float getHeight() const;
            const float getLength() const;
            const Color getColor() const;
            ~Cube();
    };
}
