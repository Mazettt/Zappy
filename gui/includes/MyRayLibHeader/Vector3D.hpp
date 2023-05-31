/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Vector3D.hpp
*/

#pragma once

namespace MyRayLib {
    class Vector3D {
        public:
            float x;
            float y;
            Vector3D() {
                this->x = 0;
                this->y = 0;
            }

            Vector3D(float x, float y) {
                this->x = x;
                this->y = y;
            }

            Vector3D operator=(const Vector3D &other) {
                this->x = other.x;
                this->y = other.y;
                return *this;
            }

            bool operator==(const Vector3D &other) {
                return (this->x == other.x && this->y == other.y);
            }

            Vector3D operator+(const Vector3D &other) {
                return Vector3D(this->x + other.x, this->y + other.y);
            }

            Vector3D operator+=(const Vector3D &other) {
                this->x += other.x;
                this->y += other.y;
                return *this;
            }

            Vector3D operator-(const Vector3D &other) {
                return Vector3D(this->x - other.x, this->y - other.y);
            }

            Vector3D operator-=(const Vector3D &other) {
                this->x -= other.x;
                this->y -= other.y;
                return *this;
            }

            Vector3D operator*(const Vector3D &other) {
                return Vector3D(this->x * other.x, this->y * other.y);
            }

            Vector3D operator*=(const Vector3D &other) {
                this->x *= other.x;
                this->y *= other.y;
                return *this;
            }

            Vector3D operator/(const Vector3D &other) {
                return Vector3D(this->x / other.x, this->y / other.y);
            }

            Vector3D operator/=(const Vector3D &other) {
                this->x /= other.x;
                this->y /= other.y;
                return *this;
            }

            ~Vector3D() {};
    };
}
