/*
** EPITECH PROJECT, 2022
** gui
** File description:
** IResource.hpp
*/

#pragma once
#include "../MyRayLibHeader/Vector3D.hpp"

namespace ZappyGui {
    class IResource {
        public:
            enum resourceType {
                BURGER,
                DERAUMERE,
                LINEMATE,
                MENDIANE,
                PHIRAS,
                SIBUR,
                THYSTAME,
                EGG,
                PLAYER,
                PLAYER_SELECTOR,
                BUTTON_START,
                BUTTON_HELP,
                BUTTON_QUIT,
                POPUP,
                LOGO,
                POPUPTILE,
                MAPDATA,
                TEAMSDATA,
                SKYBOX_BACKGROUND,
                PLAYER_STATS,
                BROADCAST,
                TIMER,
                WIN_BACKGROUND,
                BUTTON_END
            };
            virtual void draw() = 0;
            virtual IResource::resourceType getType() = 0;
            virtual void setPosition(float x, float z) = 0;
            virtual const MyRayLib::Vector3D &getPosition() = 0;
            virtual int getId() = 0;
    };
}
