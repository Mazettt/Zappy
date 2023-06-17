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
    class Draw {
        public:
            Draw() {
                BeginDrawing();
            }
            ~Draw() {
                EndDrawing();
            }
            static void MyDrawText(const char *text, int posX, int posY, int fontSize, ::Color color) {
                DrawText(text, posX, posY, fontSize, color);
            }
            static void MyImageDrawTextEx(Image *dst, const ::Font& font, const std::string &text, ::Vector2 position,
            float fontSize, float spacing, ::Color tint) {
                ImageDrawTextEx(dst, font, text.c_str(), position, fontSize, spacing, tint);
            }
            static void MyDrawFPS(int posX, int posY) {
                DrawFPS(posX, posY);
            }
            static void MyBegin3DMode(Camera3D camera) {
                BeginMode3D(camera);
            }
            static void MyEnd3DMode(void) {
                EndMode3D();
            }
            static void MyDrawCube(Vector3 position, float width, float height, float length, ::Color color) {
                DrawCube(position, width, height, length, color);
            }
            static void MyDrawCubeWires(Vector3 position, float width, float height, float length, ::Color color) {
                DrawCubeWires(position, width, height, length, color);
            }
            static void MyDrawGrid(int slices, float spacing) {
                DrawGrid(slices, spacing);
            }
            static void MyDrawModelEx(::Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, ::Color tint) {
                DrawModelEx(model, position, rotationAxis, rotationAngle, scale, tint);
            }
            static void MyDrawModel(::Model model, Vector3 position, float rotationAngle, ::Color tint) {
                DrawModel(model, position, rotationAngle, tint);
            }
            static void MyDrawTexture(::Texture2D texture, int posX, int posY, ::Color tint) {
                DrawTexture(texture, posX, posY, tint);
            }
    };
}