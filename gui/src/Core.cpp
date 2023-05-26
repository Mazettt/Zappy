/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** main.cpp
*/

#include "../includes/Core.hpp"

using namespace ZappyGui;

Core::Core()
{
    _port = 0;
    _ip = "127.0.0.1";
}

int Core::checkArgs(int ac, char **av)
{
    if (ac == 1)
        throw MyError("Core", "Not enough arguments.");
    if (ac > 5)
        throw MyError("Core", "Too many arguments.");
    if ((ac == 2) && (std::string(av[1]).find("-help") != std::string::npos)) {
        std::cout << "USAGE: ./zappy_ai -p port -h machine\n\tport\tis the port number\n\tmachine\tis the name of the machine; localhost by default" << std::endl;
        return 0;
    }

    for (int i = 0; i < ac; i++) {
        if (std::string(av[i]).find("-p") != std::string::npos) {
            if (av[i + 1] == NULL)
                throw MyError("Core", "You put the -p but no port after.");
            try {
                _port = std::stoi(av[i + 1]);
            } catch (std::exception &e) {
                throw MyError("Core", "Port is not a number.");
            }
        }
        if (std::string(av[i]).find("-h") != std::string::npos) {
            if (av[i + 1] == NULL) {
                std::cout << "[WARNING] You put the -h but no IP adress after." << std::endl;
                return 0;
            }
            for (int j = 0; av[i + 1][j] != '\0'; j++) {
                if (av[i + 1][j] == '.')
                    continue;
                else if (av[i + 1][j] < '0' || av[i + 1][j] > '9')
                    throw MyError("Core", "IP adress is not a number.");
                else
                    _ip = av[i + 1];
            }
        }
    }
    return 0;
}

int Core::handleConnectionServer(int ac, char **av)
{
    std::cout << "port: " << _port << std::endl;
    std::cout << "ip: " << _ip << std::endl;
    return 0;
}

int main(int ac, char **av)
{
    Core _core;

    try {
        _core.checkArgs(ac, av);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    _core.handleConnectionServer(ac, av);
    // MyRayLib _raylib;
    // _raylib.MyInitWindow(800, 450, "ZAPPY");
    // while (!_raylib.MyWindowShouldClose())
    // {
    //     _raylib.MyBeginDrawing();
    //         _raylib.MyClearBackground(RAYWHITE);
    //         _raylib.MyDrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
    //     _raylib.MyEndDrawing();
    // }
    return 0;
}
