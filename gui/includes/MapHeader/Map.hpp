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
#include "../MyRayLibHeader/Music.hpp"

namespace ZappyGui {
    class Map {
        private:
            Vector2 _size;
            std::vector<std::shared_ptr<Tile>> _map;
            std::vector<std::shared_ptr<Player>> _players;
            ResourceManager &_manager;
            std::shared_ptr<Player> findPlayerByID(int id);
            MyRayLib::Music _music;
            float _volumeMusicGame = 0.2;
        public:
            Map(int x, int y, ResourceManager &manager);
            ~Map();
            void addResourceForTile(const Vector2 &pos, IResource::resourceType type);
            void addPlayerForTile(const PlayerArguments &playerArgs);
            void draw();
            bool movePlayer(int playerID, float x, float z, Player::orientationAxis orientation);
            bool deadPlayer(int playerID);
            bool setPlayerLevel(int playerID, int level);
            void updateMusic();
    };
}
