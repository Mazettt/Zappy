/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** main.cpp
*/

#include "../includes/Core.hpp"
#include "../includes/MapHeader/Cube.hpp"
#include "../includes/MapHeader/Tile.hpp"
#include "../includes/MapHeader/Map.hpp"

#include "../includes/MapHeader/Map.hpp"
#include "../includes/resources/FactoryResource.hpp"
#include "../includes/MyRayLibHeader/Music.hpp"

using namespace ZappyGui;
using namespace ZappyNetworking;
using namespace MyRayLib;

Core::Core()
{
    this->_port = 0;
    this->_ip = "127.0.0.1";
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
                this->_port = std::stoi(av[i + 1]);
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
                    this->_ip = av[i + 1];
            }
        }
    }
    return 0;
}

int Core::handleConnectionServer(int ac, char **av)
{
    (void)ac;
    (void)av;
    Networking _networking;
    int sock;
    std::string message = "Hello World";
    while (true) {
        sock = _networking.connectToServer(this->_port, this->_ip);
        _networking.sendToServer(sock, message);
        std::cout << _networking.receiveFromServer() << std::endl;
    }
    return 0;
}

int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    Core _core;
    // try {
    //     _core.checkArgs(ac, av);
    //     _core.handleConnectionServer(ac, av);
    // } catch (std::exception &e) {
    //     std::cerr << e.what() << std::endl;
    //     return 84;
    // }

    int x_pos = 10;
    int y_pos = 10;
    MyRayLibWindow _raylibwindow(1920, 1080, "ZAPPY");
    Camera3D camera = _raylibwindow.MySetCameraMode((Vector3){ 0.0f, 10.0f, 50.0f }, (Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){ 0.0f, 1.0f, 0.0f }, 45.0, CAMERA_PERSPECTIVE);

    Map map(x_pos, y_pos);

    _raylibwindow.MySetTargetFPS(60);
    _raylibwindow.MyDisableCursor();
    Player player(5, 0, "Team1", {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, -90.0f, {0.6f, 0.6f, 0.6f});
    Vector3 moveSkin = {0.0f, 0.0f, 0.0f};

    // std::unique_ptr<IResource> foodeux = FactoryResource::createResource("phiras");
    float volumeMusic = 0.0;
    MyRayLib::Music music("./assets/GarfieldCoolCat.mp3");
    if (music.MyIsMusicReady())
        music.MyPlayMusic();
    while (!_raylibwindow.MyWindowShouldClose()) {
        if (_raylibwindow.MyIsKeyPressed(KEY_P) && volumeMusic < 0.9f)
            volumeMusic += 0.1f;
        if (_raylibwindow.MyIsKeyPressed(KEY_L) && volumeMusic > 0.1f)
            volumeMusic -= 0.1f;
        music.MySetMusicVolume(volumeMusic);
        music.MyUpdateMusic();
        _raylibwindow.MyUpdateCamera(&camera, CAMERA_THIRD_PERSON);
        MyRayLib::Draw _raylibdrawing;
        _raylibwindow.MyClearBackground(RAYWHITE);
        _raylibdrawing.MyBegin3DMode(camera);
        for (int y = 0; y < y_pos; ++y) {
            for (int x = 0; x < x_pos; ++x) {
                int key = y * x_pos + x;
                std::shared_ptr<Tile> &tile = map.getTile(key);
                tile->draw();
            }
        }
        moveSkin.z += 0.01;
        player.draw();
        player.move(moveSkin);
        // foodeux->draw();
        _raylibdrawing.MyEnd3DMode();
        _raylibdrawing.~Draw();
    }
    return 0;
}
