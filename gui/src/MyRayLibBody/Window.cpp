/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** RayLib.cpp
*/

#include "../../includes/MyRayLibHeader/Window.hpp"

using namespace MyRayLib;

MyRayLibWindow::MyRayLibWindow(int width, int height, const char *title)
{
    InitWindow(width, height, title);
}

MyRayLibWindow::~MyRayLibWindow(void)
{
    CloseWindow();
}

bool MyRayLibWindow::MyWindowShouldClose(void)
{
    return WindowShouldClose();
}

void MyRayLibWindow::MyClearBackground(Color color)
{
    ClearBackground(color);
}

void MyRayLibWindow::MySetTargetFPS(int fps)
{
    SetTargetFPS(fps);
}
