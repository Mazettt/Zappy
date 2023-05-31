/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** MapTile.hpp
*/

#pragma once
#include "Cube.hpp"
#include "Player.hpp"
#include "../resources/IResource.hpp"

namespace ZappyGui {
    class MapTile {
        private:
            Player _p;
            Cube _cube;
            IResource _Resources;
        public:
            const Cube getCube() const;
            MapTile(const Cube &cube);
            ~MapTile();
    };
}
