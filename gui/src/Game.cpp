/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Game.cpp
*/

#include "../includes/Game.hpp"
#include "../includes/Core.hpp"

using namespace ZappyGui;

Game::Game(const std::string &ip, int port):
    _manager(ResourceManager()),
    _camera({ 10.0f, 10.0f, 5.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0),
    _raylibwindow(MyRayLibWindow(1920, 1080, "ZAPPY")),
    _skyboxMesh(Skybox(1.0, 1.0, 1.0)),
    _raylibdrawing(),
    _ip(ip),
    _port(port),
    _map(this->_manager, this->_camera),
    _link(*this),
    _popup(),
    _showPlayerData()
{
    _manager.initialize();
}

Game::~Game() {
    // this->_manager.~ResourceManager();
    // this->_raylibwindow.~MyRayLibWindow();
    // this->_skyboxMesh.~Skybox();
    // this->_buttonMenu.clear();
}

void Game::switchToGame()
{
    try {
        this->_link.connect(_ip, _port);
        this->_stateMenu = false;
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        this->_popup.setTitle("ERROR");
        this->_popup.setDescription(e.what());
        this->_popup.setStatus(true);
    }
}

void Game::initialize() {
    this->_popup.setTexture(this->_manager.getTexture(IResource::resourceType::POPUP));
    this->_raylibwindow.MySetTargetFPS(60);

    this->_BoolCloseWin = false;
    this->_stateMenu = true;
    Button button(this->_manager.getTexture(IResource::resourceType::BUTTON_START), "./gui/assets/Buttons/buttonfx.wav", [&](){switchToGame();});
    button.ButtonSetPosition(1920/2.0f - button.button.width/2.0f, 700, (float)button.button.width, button.frameHeight);
    this->_buttonMenu.push_back(button);
    Button button2(this->_manager.getTexture(IResource::resourceType::BUTTON_HELP), "./gui/assets/Buttons/buttonfx.wav", [&](){this->_stateMenu = false;});
    button2.ButtonSetPosition(1920/2.0f - button2.button.width/2.0f, 800, (float)button2.button.width, button2.frameHeight);
    this->_buttonMenu.push_back(button2);
    Button button3(this->_manager.getTexture(IResource::resourceType::BUTTON_QUIT), "./gui/assets/Buttons/buttonfx.wav", [&](){this->_BoolCloseWin = true;});
    button3.ButtonSetPosition(1920/2.0f - button3.button.width/2.0f, 900, (float)button3.button.width, button3.frameHeight);
    this->_buttonMenu.push_back(button3);

}

void Game::run() {
    this->_skyboxMesh.InitSkybox();
    this->_skyboxMesh.chooseSkyboxFile("./gui/assets/Skybox/roh.png");

    float volumeMusic = 0.0;
    this->_raylibwindow.MyInitAudioDevice();
    MyRayLib::Music musicMenu("./gui/assets/GénériqueGarf.mp3");
    if (musicMenu.MyIsMusicReady())
        musicMenu.MyPlayMusic();

    MyRayLib::Music musicGame("./gui/assets/GarfieldCoolCat.mp3");

    while (!this->_raylibwindow.MyWindowShouldClose() && this->_BoolCloseWin == false) {
        if (_raylibwindow.MyIsKeyPressed(KEY_P) && volumeMusic < 0.9f)
                volumeMusic += 0.1f;
        if (_raylibwindow.MyIsKeyPressed(KEY_L) && volumeMusic > 0.1f)
            volumeMusic -= 0.1f;
        if (_raylibwindow.MyIsKeyPressed(KEY_ESCAPE) && this->_popup.getStatus() == true) {
            this->_popup.setStatus(false);
        }
        if (this->_stateMenu == true) {
            musicMenu.MySetMusicVolume(volumeMusic);
            musicMenu.MyUpdateMusic();
            drawMenu();
        } else {
            try {
                this->_link.update();
            } catch(const std::exception &e) {
                std::cerr << e.what() << '\n';
                this->_map.resetGame();
                this->_stateMenu = true;
            }

            if (!musicGame.MyIsMusicPlaying() && musicGame.MyIsMusicReady()) {
                musicGame.MyPlayMusic();
            }
            musicGame.MySetMusicVolume(volumeMusic);
            musicGame.MyUpdateMusic();
            // begin keys for test
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
            if (_raylibwindow.MyIsKeyPressed(KEY_V)) {
                this->_map.deadPlayer(0);
            }
            // end keys for test
            drawGame();
        }
        this->_popup.show();
        this->_raylibwindow.MyEndDrawing();
        this->_raylibdrawing.~Draw();
    }
    this->_raylibwindow.MyCloseAudioDevice();
    this->_skyboxMesh.MyUnloadShader(this->_skyboxMesh._skybox.materials[0].shader);
    this->_skyboxMesh.MyUnloadTexture(this->_skyboxMesh._skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture);
    this->_skyboxMesh.MyUnloadModel(this->_skyboxMesh._skybox);
}

void Game::drawMenu() {
        Button button0 = this->_buttonMenu.at(0);
        Button button1 = this->_buttonMenu.at(1);
        Button button2 = this->_buttonMenu.at(2);

        this->_raylibwindow.MyBeginDrawing();
        this->_raylibwindow.MyClearBackground(RAYWHITE);
        if (this->_popup.getStatus() == false) {
            button0.HandleButton();
            button1.HandleButton();
            button2.HandleButton();
        }
        this->_camera.beginMode3D();
        this->_skyboxMesh.MyrlDisableBackfaceCulling();
        this->_skyboxMesh.MyrlDisableDepthMask();
        DrawModel(this->_skyboxMesh._skybox, (Vector3){0, 0, 0}, 1.0f, WHITE);
        this->_skyboxMesh.MyrlEnableBackfaceCulling();
        this->_skyboxMesh.MyrlEnableDepthMask();
        this->_camera.updateAuto();
        this->_raylibdrawing.MyDrawGrid(10, 1.0f);
        this->_camera.endMode3D();

        button0.MyDrawTextureRec(button0.button, button0.sourceRec, (Vector2){ button0.btnBounds.x, button0.btnBounds.y }, WHITE);
        button1.MyDrawTextureRec(button1.button, button1.sourceRec, (Vector2){ button1.btnBounds.x, button1.btnBounds.y }, WHITE);
        button2.MyDrawTextureRec(button2.button, button2.sourceRec, (Vector2){ button2.btnBounds.x, button2.btnBounds.y }, WHITE);
}

void Game::drawGame() {
    this->_raylibwindow.MyClearBackground(RAYWHITE);
    this->_raylibdrawing.MyDrawFPS(10, 35);
    this->_camera.beginMode3D();
    this->_skyboxMesh.MyrlDisableBackfaceCulling();
    this->_skyboxMesh.MyrlDisableDepthMask();
    DrawModel(this->_skyboxMesh._skybox, (Vector3){0, 0, 0}, 1.0f, WHITE);
    this->_skyboxMesh.MyrlEnableBackfaceCulling();
    this->_skyboxMesh.MyrlEnableDepthMask();
    this->_camera.update();
    this->_map.draw();
    this->_camera.endMode3D();
    this->_showPlayerData.ShowDataForEachPlayer(this->_map._players);
}
