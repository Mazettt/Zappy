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
#include "Cube.hpp"
#include "../resources/FactoryResource.hpp"

namespace ZappyGui {
    class Tile {
        private:
            Cube _cube;
            std::vector<std::tuple<IResource::resourceType, float, float>> _resources;
            std::vector<std::pair<int, int>> _availablePositions;
        public:
            Tile(const Cube &cube);
            ~Tile();
            const Cube getCube() const;
            void addResource(IResource::resourceType type);
            void draw(const FactoryResource &factory);
    };
}
