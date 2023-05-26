/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** main.cpp
*/

#include "../includes/Core.hpp"

using namespace ZappyGui;

int Core::checkArgs(int ac, char **av)
{
    if (ac == 1)
        return 84;
    if ((ac == 2) && (std::string(av[1]).find("-help") != std::string::npos)) {
        std::cout << "USAGE: ./zappy_ai -p port -h machine\n\tport\tis the port number\n\tmachine\tis the name of the machine; localhost by default" << std::endl;
        return 0;
    }
    return 0;
}

int main(int ac, char **av)
{
    Core _core;
    return _core.checkArgs(ac, av);

    MyRayLib _raylib;
    _raylib.MyInitWindow(800, 450, "ZAPPY");
    while (!_raylib.MyWindowShouldClose())
    {
        _raylib.MyBeginDrawing();
            _raylib.MyClearBackground(RAYWHITE);
            _raylib.MyDrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        _raylib.MyEndDrawing();
    }
    return 0;
}
