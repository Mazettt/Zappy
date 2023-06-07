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

int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    Core _core;
    // try {
    //     _core.checkArgs(ac, av);
    //     _core.handleConnectionServer();
    // } catch (const std::exception &e) {
    //     std::cerr << e.what() << std::endl;
    //     return 84;
    // }

    int x_pos = 10;
    int y_pos = 10;
    MyRayLibWindow _raylibwindow(1920, 1080, "ZAPPY");
    Camera3D camera = _raylibwindow.MySetCameraMode({ 0.0f, 10.0f, 50.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0, CAMERA_PERSPECTIVE);

    Map map(x_pos, y_pos);

    _raylibwindow.MySetTargetFPS(60);
    // _raylibwindow.MyDisableCursor();
    Vector3 moveSkin = {0.0f, 0.0f, 0.0f};

    float volumeMusic = 0.2;
    MyRayLib::Music music("./assets/GarfieldCoolCat.mp3");
    if (music.MyIsMusicReady())
        music.MyPlayMusic();
    // MyRayLib::Music musicGen("./assets/GénériqueGarf.mp3");
    // if (musicGen.MyIsMusicReady())
    //     musicGen.MyPlayMusic();
    MyRayLib::Draw _raylibdrawing;

    bool menu = true;
    Button button("./assets/Buttons/buttonStart.png","./assets/Buttons/buttonfx.wav", [&menu](){menu = false;});
    button.ButtonSetPosition(1920/2.0f - button.button.width/2.0f, 700, (float)button.button.width, button.frameHeight);
    Button button2("./assets/Buttons/buttonHelp.png","./assets/Buttons/buttonfx.wav", [&menu](){menu = false;});
    button2.ButtonSetPosition(1920/2.0f - button2.button.width/2.0f, 800, (float)button2.button.width, button2.frameHeight);
    Button button3("./assets/Buttons/buttonQuit.png","./assets/Buttons/buttonfx.wav", [&menu](){menu = false;});
    button3.ButtonSetPosition(1920/2.0f - button3.button.width/2.0f, 900, (float)button3.button.width, button3.frameHeight);

    MyRayLib::Skybox skyboxMesh(1.0, 1.0, 1.0);
    skyboxMesh.InitSkybox();
    skyboxMesh.chooseSkyboxFile("./assets/Skybox/tt.png");

    Parallax parallax("./assets/Parallax/bkgParallax.png", "./assets/Parallax/garfTerre.png");
    while (!_raylibwindow.MyWindowShouldClose()) {
        if (menu) {
            button.HandleButton();
            button2.HandleButton();
            button3.HandleButton();

            // if (_raylibwindow.MyIsKeyPressed(KEY_P) && volumeMusic < 0.9f)
            //     volumeMusic += 0.1f;
            // if (_raylibwindow.MyIsKeyPressed(KEY_L) && volumeMusic > 0.1f)
            //     volumeMusic -= 0.1f;
            // musicGen.MySetMusicVolume(volumeMusic);
            // musicGen.MyUpdateMusic();

            _raylibwindow.MyBeginDrawing();
            parallax.updateInLoop();
            parallax.WriteTitle();

            _raylibwindow.MyClearBackground(RAYWHITE);
            button.MyDrawTextureRec(button.button, button.sourceRec, (Vector2){ button.btnBounds.x, button.btnBounds.y }, WHITE);
            button2.MyDrawTextureRec(button2.button, button2.sourceRec, (Vector2){ button2.btnBounds.x, button2.btnBounds.y }, WHITE);
            button3.MyDrawTextureRec(button3.button, button3.sourceRec, (Vector2){ button3.btnBounds.x, button3.btnBounds.y }, WHITE);
            _raylibwindow.MyEndDrawing();
        } else {
            _raylibdrawing.MyDrawFPS(10, 35);
            if (music.MyIsMusicReady())
                music.MyPlayMusic();
            if (_raylibwindow.MyIsKeyPressed(KEY_P) && volumeMusic < 0.9f)
                volumeMusic += 0.1f;
            if (_raylibwindow.MyIsKeyPressed(KEY_L) && volumeMusic > 0.1f)
                volumeMusic -= 0.1f;
            music.MySetMusicVolume(volumeMusic);
            music.MyUpdateMusic();
            _raylibwindow.MyUpdateCamera(&camera, CAMERA_THIRD_PERSON);
            _raylibwindow.MyClearBackground(RAYWHITE);
            _raylibdrawing.MyBegin3DMode(camera);
            skyboxMesh.MyrlDisableBackfaceCulling();
            skyboxMesh.MyrlDisableDepthMask();
            DrawModel(skyboxMesh._skybox, (Vector3){0, 0, 0}, 1.0f, WHITE);
            skyboxMesh.MyrlEnableBackfaceCulling();
            skyboxMesh.MyrlEnableDepthMask();
            map.draw();
            moveSkin.z += 0.01;
            _raylibdrawing.MyEnd3DMode();
        }
        _raylibdrawing.~Draw();
    }
    parallax.UnLoadFont();
    parallax.UnLoadAllParallax();
    skyboxMesh.MyUnloadShader(skyboxMesh._skybox.materials[0].shader);
    skyboxMesh.MyUnloadTexture(skyboxMesh._skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture);
    skyboxMesh.MyUnloadModel(skyboxMesh._skybox);
    return 0;
}
