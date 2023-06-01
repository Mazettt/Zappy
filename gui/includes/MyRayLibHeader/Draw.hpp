/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** Draw.hpp
*/

#pragma once

#include <iostream>
#include "raylib.h"

namespace MyRayLib {
    class MyRayLibDrawing {
        public:
            MyRayLibDrawing() {
                BeginDrawing();
            }
            ~MyRayLibDrawing() {
                EndDrawing();
            }
            void MyDrawText(const char *text, int posX, int posY, int fontSize, Color color) {
                DrawText(text, posX, posY, fontSize, color);
            }
            void MyDrawFPS(int posX, int posY) {
                DrawFPS(posX, posY);
            }
            void MyBegin3DMode(Camera3D camera) {
                BeginMode3D(camera);
            }
            void MyEnd3DMode(void) {
                EndMode3D();
            }
            void MyDrawCube(Vector3 position, float width, float height, float length, Color color) {
                DrawCube(position, width, height, length, color);
            }
            void MyDrawCubeWires(Vector3 position, float width, float height, float length, Color color) {
                DrawCubeWires(position, width, height, length, color);
            }
            void MyDrawGrid(int slices, float spacing) {
                DrawGrid(slices, spacing);
            }
            void MyDrawModelEx(::Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint) {
                DrawModelEx(model, position, rotationAxis, rotationAngle, scale, tint);
            }
        private:
    };
}