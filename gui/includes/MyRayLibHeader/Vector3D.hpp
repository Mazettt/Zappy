/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Vector3D.hpp
*/

#pragma once
#include "raylib.h"
#include <cmath>

namespace MyRayLib {
    class Vector3D {
        private:
            ::Vector3 _vector;

        public:
            Vector3D(): _vector{0.0f, 0.0f, 0.0f} {}
            Vector3D(float x, float y, float z): _vector{x, y, z} {}
            Vector3D(const Vector3D &other): _vector(other._vector) {}
            float getX() const {
                return this->_vector.x;
            }
            float getY() const {
                return this->_vector.y;
            }
            float getZ() const {
                return this->_vector.z;
            }
            void setX(float x) {
                this->_vector.x = x;
            }
            void setY(float y) {
                this->_vector.y = y;
            }
            void setZ(float z) {
                this->_vector.z = z;
            }
            Vector3 getVector3() const {
                return this->_vector;
            }
            Vector3D operator+(const Vector3D &v) const {
                return Vector3D(this->_vector.x + v.getX(), this->_vector.y + v.getY(), this->_vector.z + v.getZ());
            }
            Vector3D operator-(const Vector3D &v) const {
                return Vector3D(this->_vector.x - v.getX(), this->_vector.y - v.getY(), this->_vector.z - v.getZ());
            }
            Vector3D operator*(float scale) const {
                return Vector3D(this->_vector.x * scale, this->_vector.y * scale, this->_vector.z * scale);
            }
            float dot(const Vector3D &v) const {
                return this->_vector.x * v.getX() + this->_vector.y * v.getY() + this->_vector.z * v.getZ();
            }
            bool operator==(const Vector3D &v) const {
                return this->_vector.x == v.getX() && this->_vector.y == v.getY() && this->_vector.z == v.getZ();
            }
            bool operator!=(const Vector3D &v) const {
                return !(*this == v);
            }
            Vector3D &operator=(const Vector3D &v) {
                this->_vector = v.getVector3();
                return *this;
            }
            float length() const {
                return std::sqrt(this->_vector.x * this->_vector.x + this->_vector.y * this->_vector.y + this->_vector.z * this->_vector.z);
            }
            Vector3D normalize() const {
                float len = this->length();
                return Vector3D(this->_vector.x / len, this->_vector.y / len, this->_vector.z / len);
            }

    };
}
