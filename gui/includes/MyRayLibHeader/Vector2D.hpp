/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Vector2D.hpp
*/

#pragma once

namespace MyRayLib {
    class Vector2D {
        public:
            float x;
            float y;
            Vector2D() {
                this->x = 0;
                this->y = 0;
            }

            Vector2D(float x, float y) {
                this->x = x;
                this->y = y;
            }

            Vector2D operator=(const Vector2D &other) {
                this->x = other.x;
                this->y = other.y;
                return *this;
            }

            bool operator==(const Vector2D &other) {
                return (this->x == other.x && this->y == other.y);
            }

            Vector2D operator+(const Vector2D &other) {
                return Vector2D(this->x + other.x, this->y + other.y);
            }

            Vector2D operator+=(const Vector2D &other) {
                this->x += other.x;
                this->y += other.y;
                return *this;
            }

            Vector2D operator-(const Vector2D &other) {
                return Vector2D(this->x - other.x, this->y - other.y);
            }

            Vector2D operator-=(const Vector2D &other) {
                this->x -= other.x;
                this->y -= other.y;
                return *this;
            }

            Vector2D operator*(const Vector2D &other) {
                return Vector2D(this->x * other.x, this->y * other.y);
            }

            Vector2D operator*=(const Vector2D &other) {
                this->x *= other.x;
                this->y *= other.y;
                return *this;
            }

            Vector2D operator/(const Vector2D &other) {
                return Vector2D(this->x / other.x, this->y / other.y);
            }

            Vector2D operator/=(const Vector2D &other) {
                this->x /= other.x;
                this->y /= other.y;
                return *this;
            }

            ~Vector2D() {};
    };
}
