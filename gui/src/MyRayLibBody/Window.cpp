/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** RayLib.cpp
*/

#include "../../includes/MyRayLibHeader/Window.hpp"

using namespace MyRayLib;

void MyRayLibWindow::MyInitWindow(int width, int height, const char *title)
{
    InitWindow(width, height, title);
}

void MyRayLibWindow::MyCloseWindow(void)
{
    CloseWindow();
}

bool MyRayLibWindow::MyWindowShouldClose(void)
{
    return WindowShouldClose();
}

void MyRayLibWindow::MyBeginDrawing(void)
{
    BeginDrawing();
}

void MyRayLibWindow::MyClearBackground(Color color)
{
    ClearBackground(color);
}

// void MyRayLibWindow::MyDrawText(const char *text, int posX, int posY, int fontSize, Color color)
// {
//     DrawText(text, posX, posY, fontSize, color);
// }

void MyRayLibWindow::MyEndDrawing(void)
{
    EndDrawing();
}
