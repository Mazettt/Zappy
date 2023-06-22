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
                SetConfigFlags(FLAG_WINDOW_RESIZABLE);
                InitWindow(width, height, title);
            }
            ~MyRayLibWindow() {
                CloseWindow();
            }
            void MyBeginDrawing(void) {
                BeginDrawing();
            }
            void MyEndDrawing(void) {
                EndDrawing();
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
            float MyGetFrameTime() {
                return GetFrameTime();
            }
            void MyDisableCursor(void) {
                DisableCursor();
            }
            static void setExitKey(int key) {
                ::SetExitKey(key);
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
            static bool MyIsKeyPressed(int key) {
                return IsKeyPressed(key);
            }
            void MyInitAudioDevice() {
                InitAudioDevice();
            }
            void MyCloseAudioDevice() {
                CloseAudioDevice();
            }
            void MyToggleFullscreen() {
                ToggleFullscreen();
            }
            static int MyGetScreenWidth() {
                return GetScreenWidth();
            }
            static int MyGetScreenHeight() {
                return GetScreenHeight();
            }
            static void MySetTraceLogLevel(int logLevel) {
                SetTraceLogLevel(logLevel);
            }
    };
}
