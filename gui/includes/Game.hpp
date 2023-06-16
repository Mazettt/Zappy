/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Game.hpp
*/

#pragma once
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

using namespace MyRayLib;

namespace ZappyGui {
    class Game {
        private:
            enum stateWindow {
                GAME,
                MENU
            };
            ResourceManager _manager;
            FreeCamera _camera;
            MyRayLibWindow _raylibwindow;
            stateWindow _stateWindow;
            std::vector<Button> _buttonMenu;
            MyRayLib::Skybox _skyboxMesh;
            MyRayLib::Draw _raylibdrawing;
            bool _BoolCloseWin;
            std::string _ip;
            int _port;
            Popup _popup;
            std::shared_ptr<Player> _playerTmp;
            ServerLink _link;
            ShowPlayerData _showPlayerData;
            size_t _konamiIndex;

        public:
            Map _map;
            Game(const std::string &ip, int port);
            ~Game();
            void initialize();
            void run();
            void keyEvent(float &volumeMusic);
            void drawGame(SelectorPlayer &selectorPlayer);
            void drawMenu();
            void switchToGame();
            void checkKonamiCode(MyRayLib::Music &musicGame);
    };
}
