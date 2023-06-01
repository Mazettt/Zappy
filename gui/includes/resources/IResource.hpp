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
            virtual void draw() = 0;
            virtual void setPosition(int x, int y) = 0;
    };
}
