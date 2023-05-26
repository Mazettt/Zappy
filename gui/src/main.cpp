/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** main.cpp
*/

#include "../includes/main.hpp"
#include "../includes/EncapsulationHeader/RayLib.hpp"

int main(void)
{
    ZappyGui::MyRayLib _raylib;
    _raylib.MyInitWindow(800, 450, "raylib [core] example - basic window");
    while (!_raylib.MyWindowShouldClose())
    {
        _raylib.MyBeginDrawing();
            _raylib.MyClearBackground(RAYWHITE);
            _raylib.MyDrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        _raylib.MyEndDrawing();
    }
    return 0;
}
