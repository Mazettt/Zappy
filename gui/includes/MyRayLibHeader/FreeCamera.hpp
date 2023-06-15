/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** FreeCamera.hpp
*/

#pragma once

#include <iostream>
#include <string.h>
#include "raylib.h"

namespace MyRayLib {
    class FreeCamera {
        public:
            FreeCamera(Vector3 position, Vector3 target, Vector3 up, float fovy, int mode = CAMERA_PERSPECTIVE) {
                memset(&this->_camera, 0, sizeof(this->_camera));
                this->_camera.position = position;
                this->_camera.target = target;
                this->_camera.up = up;
                this->_camera.fovy = fovy;
                this->_camera.projection = mode;

                this->_cameraSave = this->_camera;
            }
            ~FreeCamera() {}

            void reset() {
                this->_camera.position = this->_cameraSave.position;
                this->_camera.target = this->_cameraSave.target;
                this->_camera.up = this->_cameraSave.up;
                this->_camera.fovy = this->_cameraSave.fovy;
                this->_camera.projection = this->_cameraSave.projection;
            }
            void setPosition(Vector3 position) {
                this->_camera.position = position;
            }
            void setTarget(Vector3 target) {
                this->_camera.target = target;
            }
            void updateSync(float deltaTime) {
                if (IsKeyDown(KEY_W))
                    UpdateCameraPro(&this->_camera, { 10.f * deltaTime, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f);
                if (IsKeyDown(KEY_S))
                    UpdateCameraPro(&this->_camera, { -10.f * deltaTime, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f);
                if (IsKeyDown(KEY_A))
                    UpdateCameraPro(&this->_camera, { 0.0f, -10.f * deltaTime, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f);
                if (IsKeyDown(KEY_D))
                    UpdateCameraPro(&this->_camera, { 0.0f, 10.f * deltaTime, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f);
                if (IsKeyDown(KEY_Q) || IsKeyDown(KEY_LEFT_CONTROL))
                    UpdateCameraPro(&this->_camera, { 0.0f, 0.0f, -10.f * deltaTime }, { 0.0f, 0.0f, 0.0f }, 0.0f);
                if (IsKeyDown(KEY_E) || IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_SPACE))
                    UpdateCameraPro(&this->_camera, { 0.0f, 0.0f, 10.f * deltaTime }, { 0.0f, 0.0f, 0.0f }, 0.0f);

                if (IsKeyDown(KEY_UP))
                    UpdateCameraPro(&this->_camera, { 0.0f, 0.0f, 0.0f }, { 0.0f, -80.0f * deltaTime, 0.0f }, 0.0f);
                if (IsKeyDown(KEY_DOWN))
                    UpdateCameraPro(&this->_camera, { 0.0f, 0.0f, 0.0f }, { 0.0f, 80.0f * deltaTime, 0.0f }, 0.0f);
                if (IsKeyDown(KEY_LEFT))
                    UpdateCameraPro(&this->_camera, { 0.0f, 0.0f, 0.0f }, { -80.0f * deltaTime, 0.0f, 0.0f }, 0.0f);
                if (IsKeyDown(KEY_RIGHT))
                    UpdateCameraPro(&this->_camera, { 0.0f, 0.0f, 0.0f }, { 80.0f * deltaTime, 0.0f, 0.0f }, 0.0f);
            }
            void updateOnce() {
                Vector2 mouseDelta = GetMouseDelta();
                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
                    UpdateCameraPro(&this->_camera, { 0.0f, 0.0f, 0.0f }, { mouseDelta.x / 4.0f, mouseDelta.y / 4.0f, 0.0f }, 0.0f);

                UpdateCameraPro(&this->_camera, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, -GetMouseWheelMove() * 1.5f);
            }
            void updateAuto() {
                UpdateCamera(&this->_camera, CAMERA_ORBITAL);
            }
            void beginMode3D() {
                ::BeginMode3D(this->_camera);
            }
            void endMode3D() {
                ::EndMode3D();
            }
            const ::Camera3D &getCamera() const {
                return this->_camera;
            }

        private:
            ::Camera3D _camera;
            ::Camera3D _cameraSave;
    };
}
