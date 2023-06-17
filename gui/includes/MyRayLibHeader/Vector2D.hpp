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
            ::Vector2 _vector;

        public:
            Vector2D(): _vector{0.0f, 0.0f} {}
            Vector2D(float x, float y): _vector{x, y} {}
            Vector2D(const Vector2D &other): _vector(other._vector) {}
            float getX() const {
                return this->_vector.x;
            }
            float getY() const {
                return this->_vector.y;
            }
            void setX(float x) {
                this->_vector.x = x;
            }
            void setY(float y) {
                this->_vector.y = y;
            }
            Vector2 getVector2() const {
                return this->_vector;
            }
            Vector2D operator+(const Vector2D &v) const {
                return Vector2D(this->_vector.x + v.getX(), this->_vector.y + v.getY());
            }
            Vector2D operator-(const Vector2D &v) const {
                return Vector2D(this->_vector.x - v.getX(), this->_vector.y - v.getY());
            }
            Vector2D operator*(float scale) const {
                return Vector2D(this->_vector.x * scale, this->_vector.y * scale);
            }
            float dot(const Vector2D &v) const {
                return this->_vector.x * v.getX() + this->_vector.y * v.getY();
            }
            bool operator==(const Vector2D &v) const {
                return this->_vector.x == v.getX() && this->_vector.y == v.getY();
            }
            bool operator!=(const Vector2D &v) const {
                return !(*this == v);
            }
            Vector2D &operator=(const Vector2D &v) {
                this->_vector = v.getVector2();
                return *this;
            }
    };
}
