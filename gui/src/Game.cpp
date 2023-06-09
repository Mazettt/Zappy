/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Game.cpp
*/

#include "../includes/Game.hpp"
#include "../includes/Core.hpp"

using namespace ZappyGui;

Game::Game(int mapWidth, int mapHeight): _manager(ResourceManager()), _raylibwindow(MyRayLibWindow(1920, 1080, "ZAPPY")), _skyboxMesh(Skybox(1.0, 1.0, 1.0)), _map(10, 10, this->_manager), _raylibdrawing(), _parallax(this->_manager.getTexture(IResource::resourceType::PARALLAX_MENU_BACKGROUND), this->_manager.getTexture(IResource::resourceType::PARALLAX_MENU_MIDDLE)) {
}

Game::~Game() {
    // this->_manager.~ResourceManager();
    // this->_raylibwindow.~MyRayLibWindow();
    // this->_skyboxMesh.~Skybox();
    // this->_buttonMenu.clear();
}

void Game::switchToGame()
{
    this->_stateMenu = false;
}

void Game::initialize() {
    this->_camera = this->_raylibwindow.MySetCameraMode({ 0.0f, 10.0f, 50.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0, CAMERA_PERSPECTIVE);
    this->_raylibwindow.MySetTargetFPS(60);

    this->_stateMenu = true;
    Button button(this->_manager.getTexture(IResource::resourceType::BUTTON_START), "./assets/Buttons/buttonfx.wav", [&](){switchToGame();});
    button.ButtonSetPosition(1920/2.0f - button.button.width/2.0f, 700, (float)button.button.width, button.frameHeight);
    this->_buttonMenu.push_back(button);
    Button button2(this->_manager.getTexture(IResource::resourceType::BUTTON_HELP), "./assets/Buttons/buttonfx.wav", [&](){this->_stateMenu = false;});
    button2.ButtonSetPosition(1920/2.0f - button2.button.width/2.0f, 800, (float)button2.button.width, button2.frameHeight);
    this->_buttonMenu.push_back(button2);
    Button button3(this->_manager.getTexture(IResource::resourceType::BUTTON_QUIT), "./assets/Buttons/buttonfx.wav", [&](){this->_stateMenu = false;});
    button3.ButtonSetPosition(1920/2.0f - button3.button.width/2.0f, 900, (float)button3.button.width, button3.frameHeight);
    this->_buttonMenu.push_back(button3);

}

void Game::run() {
    this->_skyboxMesh.InitSkybox();
    this->_skyboxMesh.chooseSkyboxFile("./assets/Skybox/roh.png");

    float volumeMusic = 0.2;
    // MyRayLib::Music music("./assets/GarfieldCoolCat.mp3");
    // if (music.MyIsMusicReady())
    //     music.MyPlayMusic();
    MyRayLib::Music musicGen("./assets/GénériqueGarf.mp3");
    if (musicGen.MyIsMusicReady())
        musicGen.MyPlayMusic();

    while (!this->_raylibwindow.MyWindowShouldClose()) {
        if (_raylibwindow.MyIsKeyPressed(KEY_P) && volumeMusic < 0.9f)
                volumeMusic += 0.1f;
            if (_raylibwindow.MyIsKeyPressed(KEY_L) && volumeMusic > 0.1f)
                volumeMusic -= 0.1f;
        if (this->_stateMenu == true) {
            musicGen.MySetMusicVolume(volumeMusic);
            musicGen.MyUpdateMusic();
            drawMenu();
        } else {
            // music.MySetMusicVolume(volumeMusic);
            // music.MyUpdateMusic();
            if (_raylibwindow.MyIsKeyPressed(KEY_C)) {
                int testRand;
                testRand = rand() % 3;
                this->_map.movePlayer(0, float(rand() % 9), float(rand() % 9), (testRand == 1 ? Player::orientationAxis::EAST : (testRand == 2 ? Player::orientationAxis::NORTH : (testRand == 3 ? Player::orientationAxis::SOUTH : Player::orientationAxis::WEST))));
                testRand = rand() % 3;
                this->_map.movePlayer(1, float(rand() % 9), float(rand() % 9), (testRand == 1 ? Player::orientationAxis::EAST : (testRand == 2 ? Player::orientationAxis::NORTH : (testRand == 3 ? Player::orientationAxis::SOUTH : Player::orientationAxis::WEST))));
                testRand = rand() % 3;
                this->_map.movePlayer(2, float(rand() % 9), float(rand() % 9), (testRand == 1 ? Player::orientationAxis::EAST : (testRand == 2 ? Player::orientationAxis::NORTH : (testRand == 3 ? Player::orientationAxis::SOUTH : Player::orientationAxis::WEST))));
                testRand = rand() % 3;
                this->_map.movePlayer(3, float(rand() % 9), float(rand() % 9), (testRand == 1 ? Player::orientationAxis::EAST : (testRand == 2 ? Player::orientationAxis::NORTH : (testRand == 3 ? Player::orientationAxis::SOUTH : Player::orientationAxis::WEST))));
            }
            drawGame();
            if (_raylibwindow.MyIsKeyPressed(KEY_V)) {
                this->_map.deadPlayer(0);
            }
            drawGame();
        }
        this->_raylibdrawing.~Draw();
    }
    this->_skyboxMesh.MyUnloadShader(this->_skyboxMesh._skybox.materials[0].shader);
    this->_skyboxMesh.MyUnloadTexture(this->_skyboxMesh._skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture);
    this->_skyboxMesh.MyUnloadModel(this->_skyboxMesh._skybox);
    this->_parallax.UnLoadFont();
    this->_parallax.UnLoadAllParallax();
}

void Game::drawMenu() {
        Button button0 = this->_buttonMenu.at(0);
        Button button1 = this->_buttonMenu.at(1);
        Button button2 = this->_buttonMenu.at(2);


        this->_raylibwindow.MyBeginDrawing();
        this->_raylibwindow.MyClearBackground(RAYWHITE);
        button0.HandleButton();
        button1.HandleButton();
        button2.HandleButton();

        this->_parallax.updateInLoop();
        this->_parallax.WriteTitle();

        button0.MyDrawTextureRec(button0.button, button0.sourceRec, (Vector2){ button0.btnBounds.x, button0.btnBounds.y }, WHITE);
        button1.MyDrawTextureRec(button1.button, button1.sourceRec, (Vector2){ button1.btnBounds.x, button1.btnBounds.y }, WHITE);
        button2.MyDrawTextureRec(button2.button, button2.sourceRec, (Vector2){ button2.btnBounds.x, button2.btnBounds.y }, WHITE);
        this->_raylibwindow.MyEndDrawing();

}

void Game::drawGame() {
    this->_raylibwindow.MyClearBackground(RAYWHITE);
    this->_raylibdrawing.MyDrawFPS(10, 35);
    this->_raylibdrawing.MyBegin3DMode(this->_camera);
    this->_skyboxMesh.MyrlDisableBackfaceCulling();
    this->_skyboxMesh.MyrlDisableDepthMask();
    DrawModel(this->_skyboxMesh._skybox, (Vector3){0, 0, 0}, 1.0f, WHITE);
    this->_skyboxMesh.MyrlEnableBackfaceCulling();
    this->_skyboxMesh.MyrlEnableDepthMask();
    this->_raylibwindow.MyUpdateCamera(&this->_camera, CAMERA_THIRD_PERSON);
    this->_map.draw();
    this->_raylibdrawing.MyEnd3DMode();
}
