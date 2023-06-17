/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Vector2D.hpp
*/

#pragma once
#include "raylib.h"
#include <cmath>

namespace MyRayLib {
    class Vector2D {
        private:
            ::Vector2 vector;

        public:
            Vector2D(): vector{0.0f, 0.0f} {}
            Vector2D(float x, float y): vector{x, y} {}
            float getX() const {
                return vector.x;
            }
            float getY() const {
                return vector.y;
            }
            void setX(float x) {
                vector.x = x;
            }
            void setY(float y) {
                vector.y = y;
            }
            Vector2 getVector2() const {
                return vector;
            }
            Vector2D operator+(const Vector2D &v) const {
                return Vector2D(vector.x + v.getX(), vector.y + v.getY());
            }
            Vector2D operator-(const Vector2D &v) const {
                return Vector2D(vector.x - v.getX(), vector.y - v.getY());
            }
            Vector2D operator*(float scale) const {
                return Vector2D(vector.x * scale, vector.y * scale);
            }
            float dot(const Vector2D &v) const {
                return vector.x * v.getX() + vector.y * v.getY();
            }
            bool operator==(const Vector2D &v) const {
                return vector.x == v.getX() && vector.y == v.getY();
            }
            bool operator!=(const Vector2D &v) const {
                return !(*this == v);
            }
            Vector2D &operator=(const Vector2D &v) {
                vector = v.getVector2();
                return *this;
            }
    };
}
