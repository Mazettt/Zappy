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
            // Player _p;
            Cube _cube;
            std::vector<std::pair<std::unique_ptr<IResource>, int>> _Resources;
        public:
            Tile(const Cube &cube);
            ~Tile();
            const Cube getCube() const;
            void addResource(int keyResource, int quantity);
    };
}
