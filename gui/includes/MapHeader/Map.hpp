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
#include "../resources/FactoryResource.hpp"

namespace ZappyGui {
    class Map {
        private:
            int _sizeX;
            int _sizeY;
            std::vector<std::shared_ptr<Tile>> _map;
            FactoryResource _factory;
        public:
            Map(int x, int y);
            ~Map();
            std::vector<std::shared_ptr<Tile>> getMap();
            std::shared_ptr<Tile> &getTile(int key);
            void addResourceForTile(int posX, int posY, IResource::resourceType type);
            void draw();
    };
}
