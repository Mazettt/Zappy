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
            ::Vector3 vector;

        public:
            Vector3D(): vector{0.0f, 0.0f, 0.0f} {}
            Vector3D(float x, float y, float z): vector{x, y, z} {}
            float getX() const {
                return vector.x;
            }
            float getY() const {
                return vector.y;
            }
            float getZ() const {
                return vector.z;
            }
            void setX(float x) {
                vector.x = x;
            }
            void setY(float y) {
                vector.y = y;
            }
            void setZ(float z) {
                vector.z = z;
            }
            Vector3 getVector3() const {
                return vector;
            }
            Vector3D operator+(const Vector3D &v) const {
                return Vector3D(vector.x + v.getX(), vector.y + v.getY(), vector.z + v.getZ());
            }
            Vector3D operator-(const Vector3D &v) const {
                return Vector3D(vector.x - v.getX(), vector.y - v.getY(), vector.z - v.getZ());
            }
            Vector3D operator*(float scale) const {
                return Vector3D(vector.x * scale, vector.y * scale, vector.z * scale);
            }
            float dot(const Vector3D &v) const {
                return vector.x * v.getX() + vector.y * v.getY() + vector.z * v.getZ();
            }
            bool operator==(const Vector3D &v) const {
                return vector.x == v.getX() && vector.y == v.getY() && vector.z == v.getZ();
            }
            bool operator!=(const Vector3D &v) const {
                return !(*this == v);
            }
            Vector3D &operator=(const Vector3D &v) {
                vector = v.getVector3();
                return *this;
            }
    };
}
