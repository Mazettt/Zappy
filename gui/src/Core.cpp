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

#include "../includes/MapHeader/Map.hpp"
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
    Camera3D camera = _raylibwindow.MySetCameraMode({ 0.0f, 10.0f, 50.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0, CAMERA_PERSPECTIVE);

    Map map(x_pos, y_pos);

    _raylibwindow.MySetTargetFPS(60);
    // _raylibwindow.MyDisableCursor();
    Vector3 moveSkin = {0.0f, 0.0f, 0.0f};

    float volumeMusic = 0.5;
    MyRayLib::Music music("./assets/GarfieldCoolCat.mp3");
    if (music.MyIsMusicReady())
        music.MyPlayMusic();
    MyRayLib::Draw _raylibdrawing;

    Button button("./assets/Buttons/button.png","./assets/Buttons/buttonfx.wav");
    button.ButtonSetPosition(1920/2.0f - button.button.width/2.0f, 1080/2.0f - button.button.height/3/2.0f, (float)button.button.width, button.frameHeight);
    // MyRayLib::Skybox skyboxMesh(1.0, 1.0, 1.0);
    // skyboxMesh.MyLoadFromMesh(skyboxMesh._cube);

    // int a[1] = { MATERIAL_MAP_CUBEMAP };
    // int b[1] = { skyboxMesh._useHDR ? 1 : 0 };
    // int c[1] = { skyboxMesh._useHDR ? 1 : 0 };
    // int d[1] = { 0 };

    // skyboxMesh._skybox.materials[0].shader = skyboxMesh.MyLoadShader("./assets/Skybox/skybox.vs", "./assets/Skybox/skybox.fs");

    // skyboxMesh.MySetShaderValue(skyboxMesh._skybox.materials[0].shader, skyboxMesh.MyGetShaderLocation(skyboxMesh._skybox.materials[0].shader, "environmentMap"), a, SHADER_UNIFORM_INT);
    // skyboxMesh.MySetShaderValue(skyboxMesh._skybox.materials[0].shader, skyboxMesh.MyGetShaderLocation(skyboxMesh._skybox.materials[0].shader, "doGamma"), b, SHADER_UNIFORM_INT);
    // skyboxMesh.MySetShaderValue(skyboxMesh._skybox.materials[0].shader, skyboxMesh.MyGetShaderLocation(skyboxMesh._skybox.materials[0].shader, "vflipped"), c, SHADER_UNIFORM_INT);

    // skyboxMesh._shdrCubemap = skyboxMesh.MyLoadShader("./assets/Skybox/cubemap.vs", "./assets/Skybox/cubemap.fs");
    // skyboxMesh.MySetShaderValue(skyboxMesh._shdrCubemap, skyboxMesh.MyGetShaderLocation(skyboxMesh._shdrCubemap, "environmentMap"), a, SHADER_UNIFORM_INT);

    // if (skyboxMesh._useHDR) {
    //     skyboxMesh.MyTextCopy(skyboxMesh._skyboxFileName, "./assets/Skybox/skybox.png");
    //     skyboxMesh._panorama = skyboxMesh.MyLoadTexture(skyboxMesh._skyboxFileName);
    //     skyboxMesh._skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = skyboxMesh.MyGenTextureCubemap(skyboxMesh._shdrCubemap, 1024, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    // } else {
    //     skyboxMesh._img = skyboxMesh.MyLoadImage("./assets/Skybox/skybox.png");
    //     skyboxMesh._skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = LoadTextureCubemap(skyboxMesh._img, CUBEMAP_LAYOUT_AUTO_DETECT);    // CUBEMAP_LAYOUT_PANORAMA
    //     skyboxMesh.MyUnloadImage(skyboxMesh._img);
    // }
    bool menu = true;
    while (!_raylibwindow.MyWindowShouldClose()) {
        if (menu) {
            button.mousePoint = GetMousePosition();
            button.btnAction = false;

            if (button.MyCheckCollisionPointRec(button.mousePoint, button.btnBounds)) {
                if (button.MyIsMouseButtonDown(MOUSE_BUTTON_LEFT))
                    button.btnState = 2;
                else
                    button.btnState = 1;

                if (button.MyIsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                    button.btnAction = true;
            }
            else
                button.btnState = 0;

            if (button.btnAction) {
                button.MyPlaySound(button.SoundButton);
                menu = false;
            }

            button.sourceRec.y = button.btnState*button.frameHeight;
            _raylibwindow.MyBeginDrawing();
            _raylibwindow.MyClearBackground(RAYWHITE);
            button.MyDrawTextureRec(button.button, button.sourceRec, (Vector2){ button.btnBounds.x, button.btnBounds.y }, WHITE);
            _raylibwindow.MyEndDrawing();
        } else {
            _raylibdrawing.MyDrawFPS(10, 35);
            if (_raylibwindow.MyIsKeyPressed(KEY_P) && volumeMusic < 0.9f)
                volumeMusic += 0.1f;
            if (_raylibwindow.MyIsKeyPressed(KEY_L) && volumeMusic > 0.1f)
                volumeMusic -= 0.1f;
            music.MySetMusicVolume(volumeMusic);
            music.MyUpdateMusic();
            _raylibwindow.MyUpdateCamera(&camera, CAMERA_THIRD_PERSON);
            _raylibwindow.MyClearBackground(RAYWHITE);
            _raylibdrawing.MyBegin3DMode(camera);
            // skyboxMesh.MyrlDisableBackfaceCulling();
            // skyboxMesh.MyrlDisableDepthMask();
            // DrawModel(skyboxMesh._skybox, (Vector3){0, 0, 0}, 1.0f, WHITE);
            map.draw();
            moveSkin.z += 0.01;
            // skyboxMesh.MyrlEnableBackfaceCulling();
            // skyboxMesh.MyrlEnableDepthMask();
            _raylibdrawing.MyEnd3DMode();
        }
        _raylibdrawing.~Draw();
    }
    // skyboxMesh.MyUnloadShader(skyboxMesh._skybox.materials[0].shader);
    // skyboxMesh.MyUnloadTexture(skyboxMesh._skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture);
    // skyboxMesh.MyUnloadModel(skyboxMesh._skybox);
    return 0;
}
