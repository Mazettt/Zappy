/*
** EPITECH PROJECT, 2022
** gui
** File description:
** IResource.hpp
*/

#pragma once
#include "raylib.h"

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
                BUTTON_START,
                BUTTON_HELP,
                BUTTON_QUIT,
                PARALLAX_MENU_BACKGROUND,
                PARALLAX_MENU_MIDDLE
            };
            virtual void draw() = 0;
            virtual IResource::resourceType getType() = 0;
            virtual void setPosition(float x, float z) = 0;
            virtual const Vector3 &getPosition() = 0;
    };
}
