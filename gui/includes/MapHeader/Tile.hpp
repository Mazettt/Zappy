/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Tile.hpp
*/

#pragma once
#include "Cube.hpp"
#include "Player.hpp"
#include <vector>
#include <memory>
#include "../resources/IResource.hpp"

namespace ZappyGui {
    class Tile {
        private:
            Cube _cube;
            std::vector<std::unique_ptr<IResource>> _resources;
            std::vector<std::pair<int, int>> _availablePositions;
        public:
            Tile(const Cube &cube);
            ~Tile();
            const Cube getCube() const;
            void addResource(int keyResource, int quantity);
            void draw();
    };
}
