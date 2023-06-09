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

#include "MapHeader/Map.hpp"
#include "MyRayLibHeader/Music.hpp"

using namespace MyRayLib;

namespace ZappyGui {
    class Game {
        private:
            // Map _map;
            ResourceManager _manager;
            Camera3D _camera;
            MyRayLibWindow _raylibwindow;
            bool _stateMenu;
            std::vector<Button> _buttonMenu;
            MyRayLib::Skybox _skyboxMesh;
            Map _map;
            MyRayLib::Draw _raylibdrawing;
        public:
            Parallax _parallax;
            Game(int mapWidth, int mapHeight);
            ~Game();
            void initialize();
            void run();
            void drawGame();
            void drawMenu();
            void switchToGame();
    };
}
