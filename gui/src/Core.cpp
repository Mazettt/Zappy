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
#include "../includes/MyRayLibHeader/Skybox.hpp"
#include "../includes/MyRayLibHeader/Button.hpp"
#include "../includes/MyRayLibHeader/Parallax.hpp"
#include "../includes/MyRayLibHeader/Shader.hpp"

#include "../includes/MapHeader/Map.hpp"
#include "../includes/MyRayLibHeader/Music.hpp"

using namespace ZappyGui;
using namespace ZappyNetworking;
using namespace MyRayLib;

Core::Core()
{
    this->_port = 4242;
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

int Core::handleConnectionServer()
{
    _server.connect(this->_ip, this->_port);
    while (true) {
        _server.update();
    }
    return 0;
}

// TO REMOVE

    // Shader shaders[7] = {0};
    // shaders[0] = LoadShader(0, "./assets/Shaders/chromaberration.fs");
    // shaders[1] = LoadShader(0, "./assets/Shaders/clown.fs");
    // shaders[2] = LoadShader(0, "./assets/Shaders/degueuvert.fs");
    // shaders[3] = LoadShader(0, "./assets/Shaders/fragment.fs");
    // shaders[4] = LoadShader(0, "./assets/Shaders/gaussian.fs");
    // shaders[5] = LoadShader(0, "./assets/Shaders/nightvis.fs");
    // shaders[6] = LoadShader(0, "./assets/Shaders/predator.fs");
    // int shader = 0;
    // int shaderMax = 7;


    // MyRayLib::Skybox skyboxMesh(1.0, 1.0, 1.0);
    // skyboxMesh.InitSkybox();
    // skyboxMesh.chooseSkyboxFile("./assets/Skybox/tt.png");

    // while (!_raylibwindow.MyWindowShouldClose()) {
        // if (IsKeyPressed(KEY_J)) {
        //     shader--;
        //     if (shader < 0)
        //         shader = shaderMax - 1;
        // }
        // if (IsKeyPressed(KEY_K)) {
        //     shader++;
        //     if (shader > shaderMax - 1)
        //         shader = 0;
        // }
        // if (menu) {
        // } else {
            // BeginShaderMode(shaders[shader]);
            // skyboxMesh.MyrlDisableBackfaceCulling();
            // skyboxMesh.MyrlDisableDepthMask();
            // DrawModel(skyboxMesh._skybox, (Vector3){0, 0, 0}, 1.0f, WHITE);
            // skyboxMesh.MyrlEnableBackfaceCulling();
            // skyboxMesh.MyrlEnableDepthMask();
    //     }
    // }
    // skyboxMesh.MyUnloadShader(skyboxMesh._skybox.materials[0].shader);
    // skyboxMesh.MyUnloadTexture(skyboxMesh._skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture);
    // skyboxMesh.MyUnloadModel(skyboxMesh._skybox);
    // return 0;
// }
