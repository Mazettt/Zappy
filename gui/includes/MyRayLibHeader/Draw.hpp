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
            MyRayLibDrawing();
            ~MyRayLibDrawing();
            void MyDrawText(const char *text, int posX, int posY, int fontSize, Color color);
            void MyDrawFPS(int posX, int posY);
            void MyBegin3DMode(Camera3D camera);
            void MyEnd3DMode(void);
            void MyDrawCube(Vector3 position, float width, float height, float length, Color color);
            void MyDrawCubeWires(Vector3 position, float width, float height, float length, Color color);
            void MyDrawGrid(int slices, float spacing);
        private:
    };
}