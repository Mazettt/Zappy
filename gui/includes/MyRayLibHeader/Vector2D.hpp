/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Vector2D.hpp
*/

#pragma once

namespace MyRayLib {
    class MyRayLibVector2D {
        public:
            float x;
            float y;
            MyRayLibVector2D() {
                this->x = 0;
                this->y = 0;
            }

            MyRayLibVector2D(float x, float y) {
                this->x = x;
                this->y = y;
            }

            MyRayLibVector2D operator=(const MyRayLibVector2D &other) {
                this->x = other.x;
                this->y = other.y;
                return *this;
            }

            bool operator==(const MyRayLibVector2D &other) {
                return (this->x == other.x && this->y == other.y);
            }

            MyRayLibVector2D operator+(const MyRayLibVector2D &other) {
                return MyRayLibVector2D(this->x + other.x, this->y + other.y);
            }

            MyRayLibVector2D operator+=(const MyRayLibVector2D &other) {
                this->x += other.x;
                this->y += other.y;
                return *this;
            }

            MyRayLibVector2D operator-(const MyRayLibVector2D &other) {
                return MyRayLibVector2D(this->x - other.x, this->y - other.y);
            }

            MyRayLibVector2D operator-=(const MyRayLibVector2D &other) {
                this->x -= other.x;
                this->y -= other.y;
                return *this;
            }

            MyRayLibVector2D operator*(const MyRayLibVector2D &other) {
                return MyRayLibVector2D(this->x * other.x, this->y * other.y);
            }

            MyRayLibVector2D operator*=(const MyRayLibVector2D &other) {
                this->x *= other.x;
                this->y *= other.y;
                return *this;
            }

            MyRayLibVector2D operator/(const MyRayLibVector2D &other) {
                return MyRayLibVector2D(this->x / other.x, this->y / other.y);
            }

            MyRayLibVector2D operator/=(const MyRayLibVector2D &other) {
                this->x /= other.x;
                this->y /= other.y;
                return *this;
            }

            ~MyRayLibVector2D() {};
    };
}
