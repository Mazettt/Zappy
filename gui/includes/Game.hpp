/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Game.hpp
*/

#pragma once
#include <thread>
#include <vector>
#include <functional>

#include "MapHeader/Cube.hpp"
#include "MapHeader/Tile.hpp"
#include "MapHeader/Map.hpp"
#include "MyRayLibHeader/Skybox.hpp"
#include "MyRayLibHeader/Button.hpp"
#include "MyRayLibHeader/FreeCamera.hpp"
#include "Server/ServerLink.hpp"
#include "Popup.hpp"
#include "./MapHeader/ShowPlayerData.hpp"
#include "../includes/MapHeader/SelectorPlayer.hpp"

#include "MapHeader/Map.hpp"
#include "Timer.hpp"

using namespace MyRayLib;

namespace ZappyGui {
    class Game {
        private:
            enum stateWindow {
                GAME,
                MENU,
                PRELOADING,
                WIN
            };
            stateWindow _stateWindow;
            ResourceManager _manager;
            FreeCamera _camera;
            MyRayLibWindow _raylibwindow;
            std::vector<Button> _buttonMenu;
            MyRayLib::Skybox _skyboxMesh;
            MyRayLib::Draw _raylibdrawing;
            bool _BoolCloseWin;
            std::string _ip;
            int _port;
            std::shared_ptr<Player> _playerTmp;
            ServerLink _link;
            ShowPlayerData _showPlayerData;
            size_t _konamiIndex;
            std::thread _resourceThread;
            bool showTeams;
            Timer _timer;
            std::string _winnerTeam;

        public:
            Popup _popup;
            Map _map;
            Game(const std::string &ip, int port);
            ~Game();
            void initializeButton();
            void run();
            void keyEvent(float &volumeMusic);
            void drawGame(SelectorPlayer &selectorPlayer);
            void drawMenu();
            void drawLoading();
            void switchToGame();
            void checkKonamiCode(MyRayLib::Music &musicGame);
            void drawMapData();
            void drawTeamsData();
            void drawWinScreen();
            void setWin(const std::string &winnerTeam);
            void startTimer();
    };
}
