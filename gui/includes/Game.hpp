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
#include "MyRayLibHeader/Parallax.hpp"
#include "Server/ServerLink.hpp"
#include "Popup.hpp"

#include "MapHeader/Map.hpp"

using namespace MyRayLib;

namespace ZappyGui {
    class Game {
        private:
            ResourceManager _manager;
            Camera3D _camera;
            MyRayLibWindow _raylibwindow;
            bool _stateMenu;
            std::vector<Button> _buttonMenu;
            MyRayLib::Skybox _skyboxMesh;
            MyRayLib::Draw _raylibdrawing;
            bool _BoolCloseWin;
            Parallax _parallax;
            std::string _ip;
            int _port;
            Popup _popup;
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
