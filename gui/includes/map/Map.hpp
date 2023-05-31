/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Map.hpp
*/

#pragma once
#include <vector>
#include <memory>
#include "Tile.hpp"

namespace ZappyGui {
    class Map {
        private:
            int _sizeX;
            int _sizeY;
            std::vector<std::shared_ptr<Tile>> _map;
        public:
            Map(int x, int y);
            ~Map();
            std::vector<std::shared_ptr<Tile>> getMap();
            std::shared_ptr<Tile> &getTile(int key);
            void addResourceForTile(int posX, int posY, int keyResource, int quantity);
    };
}
