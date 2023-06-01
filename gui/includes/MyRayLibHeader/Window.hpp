/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** RayLib.hpp
*/

#pragma once

#include <iostream>
#include "raylib.h"

namespace MyRayLib {
    class MyRayLibWindow {
        public:
            MyRayLibWindow(int width, int height, const char *title) {
                InitWindow(width, height, title);
            }
            ~MyRayLibWindow() {
                CloseWindow();
            }
            bool MyWindowShouldClose(void) {
                return WindowShouldClose();
            }
            void MyClearBackground(Color color) {
                ClearBackground(color);
            }
            void MySetTargetFPS(int fps) {
                SetTargetFPS(fps);
            }
            void MyDisableCursor(void) {
                DisableCursor();
            }
            Camera3D MySetCameraMode(Vector3 position, Vector3 target, Vector3 up, float fovy, int mode) {
                Camera3D camera = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
                camera.position = position;
                camera.target = target;
                camera.up = up;
                camera.fovy = fovy;
                camera.projection = mode;
                return camera;
            }
            void MyUpdateCamera(Camera *camera, int mode) {
                UpdateCamera(camera, mode);
            }
        protected:
        private:
    };
}
