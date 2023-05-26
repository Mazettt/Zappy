/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** RayLib.cpp
*/

#include "../../includes/EncapsulationHeader/RayLib.hpp"

using namespace ZappyGui;

void MyRayLib::MyInitWindow(int width, int height, const char *title)
{
    InitWindow(width, height, title);
}

void MyRayLib::MyCloseWindow(void)
{
    CloseWindow();
}

bool MyRayLib::MyWindowShouldClose(void)
{
    return WindowShouldClose();
}

void MyRayLib::MyBeginDrawing(void)
{
    BeginDrawing();
}

void MyRayLib::MyClearBackground(Color color)
{
    ClearBackground(color);
}

void MyRayLib::MyDrawText(const char *text, int posX, int posY, int fontSize, Color color)
{
    DrawText(text, posX, posY, fontSize, color);
}

void MyRayLib::MyEndDrawing(void)
{
    EndDrawing();
}
