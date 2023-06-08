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
            Vector2 _size;
            std::vector<std::shared_ptr<Tile>> _map;
            std::vector<std::unique_ptr<Player>> _players;
            ResourceManager &_manager;
        public:
            Map(int x, int y, ResourceManager &manager);
            ~Map();
            void addResourceForTile(const Vector2 &pos, IResource::resourceType type);
            void addPlayerForTile(const PlayerArguments &playerArgs);
            void draw();
            void movePlayer(int playerNumber, float x, float z);
    };
}
