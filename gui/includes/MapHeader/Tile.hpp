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
#include "Cube.hpp"
#include "../resources/IResource.hpp"
#include "../resources/FactoryResource.hpp"

namespace ZappyGui {
    class Tile {
        public:
            std::vector<std::unique_ptr<IResource>> _resources;
            std::vector<std::pair<int, int>> _availablePositions;
            Cube _cube;
            Tile(const Cube &cube);
            ~Tile();
            void addResource(const ResourceManager &manager, IResource::resourceType type);
            void removeResource(const IResource::resourceType type);
            void addPlayer(const ResourceManager &manager, IResource::resourceType type, const PlayerArguments &playerArgs);
            void draw();
            void drawContentPopup(const MyRayLib::Texture2D &texture);
            int countSpecificResource(IResource::resourceType type);
    };
}
