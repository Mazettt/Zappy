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

#include "MapHeader/Map.hpp"

using namespace MyRayLib;

namespace ZappyGui {
    class Game {
        private:
            ResourceManager _manager;
            FreeCamera _camera;
            MyRayLibWindow _raylibwindow;
            bool _stateMenu;
            std::vector<Button> _buttonMenu;
            MyRayLib::Skybox _skyboxMesh;
            MyRayLib::Draw _raylibdrawing;
            bool _BoolCloseWin;
            std::string _ip;
            int _port;
            Popup _popup;
            ShowPlayerData _showPlayerData;
            std::shared_ptr<Player> _playerTmp;
        public:
            Map _map;
            Game(const std::string &ip, int port);
            ~Game();
            void initialize();
            void run();
            void drawGame();
            void drawMenu();
            void switchToGame();
            ServerLink _link;
    };
}
