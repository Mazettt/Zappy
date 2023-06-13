/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Cube.hpp
*/
#pragma once
#include "../MyRayLibHeader/Vector3D.hpp"
#include "../MyRayLibHeader/Draw.hpp"
#include "../MyRayLibHeader/Color.hpp"
// #include "raylib.h"

namespace ZappyGui {
    class Cube {
        private:
            Vector3 _pos;
            float _width;
            float _height;
            float _length;

        public:
            Color _color;
            Cube(Vector3 pos, float width, float height, float length, Color color);
            Cube(const Cube& other);
            Cube &operator=(const Cube &cube);
            Vector3 getPos() const;
            float getWidth() const;
            float getHeight() const;
            float getLength() const;
            Color getColor() const;
            void draw();
            ~Cube();
    };
}
