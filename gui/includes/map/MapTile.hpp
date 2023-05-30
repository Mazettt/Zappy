/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** MapTile.hpp
*/

#pragma once
#include "Cube.hpp"
#include "Player.hpp"
#include "Ressource.hpp"

namespace ZappyGui {
    class MapTile {
        private:
            Player _p;
            Cube _cube;
            Ressource _ressources;
        public:
            const Cube getCube() const;
            MapTile(const Cube &cube);
            ~MapTile();
    };
}
