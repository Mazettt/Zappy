/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** main.cpp
*/

#include "../includes/Core.hpp"

using namespace ZappyGui;
using namespace ZappyNetworking;
using namespace MyRayLib;

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
    Networking _networking;
    int sock;
    std::string message = "Hello World";
    while (true) {
        sock = _networking.connectToServer(_port, _ip);
        _networking.sendToServer(sock, message);
        std::cout << _networking.receiveFromServer() << std::endl;
    }
    return 0;
}

int main(int ac, char **av)
{
    // Core _core;
    // try {
    //     _core.checkArgs(ac, av);
    //     _core.handleConnectionServer(ac, av);
    // } catch (std::exception &e) {
    //     std::cerr << e.what() << std::endl;
    //     return 84;
    // }
    MyRayLibWindow _raylibwindow(1920, 1080, "ZAPPY");
    Camera3D camera = _raylibwindow.MySetCameraMode((Vector3){ 0.0f, 10.0f, 10.0f }, (Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){ 0.0f, 1.0f, 0.0f }, 45.0, CAMERA_PERSPECTIVE);

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };
    _raylibwindow.MySetTargetFPS(60);
    while (!_raylibwindow.MyWindowShouldClose()) {
        MyRayLibDrawing _raylibdrawing;
        _raylibwindow.MyClearBackground(RAYWHITE);
        _raylibdrawing.MyBegin3DMode(camera);

        _raylibdrawing.MyDrawGrid(10, 1.0f);

        _raylibdrawing.MyEnd3DMode();
        _raylibdrawing.~MyRayLibDrawing();
    }
    return 0;
}
