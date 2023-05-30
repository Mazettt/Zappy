/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** Draw.cpp
*/

#include "../../includes/MyRayLibHeader/Draw.hpp"

using namespace MyRayLib;

MyRayLibDrawing::MyRayLibDrawing()
{
    BeginDrawing();
}

MyRayLibDrawing::~MyRayLibDrawing()
{
    EndDrawing();
}

void MyRayLibDrawing::MyDrawText(const char *text, int posX, int posY, int fontSize, Color color)
{
    DrawText(text, posX, posY, fontSize, color);
}

void MyRayLibDrawing::MyDrawFPS(int posX, int posY)
{
    DrawFPS(posX, posY);
}

void MyRayLibDrawing::MyBegin3DMode(Camera3D camera)
{
    BeginMode3D(camera);
}

void MyRayLibDrawing::MyEnd3DMode(void)
{
    EndMode3D();
}

void MyRayLibDrawing::MyDrawCube(Vector3 position, float width, float height, float length, Color color)
{
    DrawCube(position, width, height, length, color);
}

void MyRayLibDrawing::MyDrawCubeWires(Vector3 position, float width, float height, float length, Color color)
{
    DrawCubeWires(position, width, height, length, color);
}

void MyRayLibDrawing::MyDrawGrid(int slices, float spacing)
{
    DrawGrid(slices, spacing);
}
