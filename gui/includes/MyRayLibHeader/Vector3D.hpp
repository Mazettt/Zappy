/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Vector3D.hpp
*/

#pragma once

namespace MyRayLib {
    class MyRayLibVector3D {
        public:
            float x;
            float y;
            MyRayLibVector3D() {
                this->x = 0;
                this->y = 0;
            }

            MyRayLibVector3D(float x, float y) {
                this->x = x;
                this->y = y;
            }

            // MyRayLibVector3D operator=(const MyRayLibVector3D &other) {
            //     this->x = other.x;
            //     this->y = other.y;
            //     return *this;
            // }

            // bool operator==(const MyRayLibVector3D &other) {
            //     return (this->x == other.x && this->y == other.y);
            // }

            // MyRayLibVector3D operator+(const MyRayLibVector3D &other) {
            //     return MyRayLibVector3D(this->x + other.x, this->y + other.y);
            // }

            // MyRayLibVector3D operator+=(const MyRayLibVector3D &other) {
            //     this->x += other.x;
            //     this->y += other.y;
            //     return *this;
            // }

            // MyRayLibVector3D operator-(const MyRayLibVector3D &other) {
            //     return MyRayLibVector3D(this->x - other.x, this->y - other.y);
            // }

            // MyRayLibVector3D operator-=(const MyRayLibVector3D &other) {
            //     this->x -= other.x;
            //     this->y -= other.y;
            //     return *this;
            // }

            // MyRayLibVector3D operator*(const MyRayLibVector3D &other) {
            //     return MyRayLibVector3D(this->x * other.x, this->y * other.y);
            // }

            // MyRayLibVector3D operator*=(const MyRayLibVector3D &other) {
            //     this->x *= other.x;
            //     this->y *= other.y;
            //     return *this;
            // }

            // MyRayLibVector3D operator/(const MyRayLibVector3D &other) {
            //     return MyRayLibVector3D(this->x / other.x, this->y / other.y);
            // }

            // MyRayLibVector3D operator/=(const MyRayLibVector3D &other) {
            //     this->x /= other.x;
            //     this->y /= other.y;
            //     return *this;
            // }

            ~MyRayLibVector3D() {};
    };
}
