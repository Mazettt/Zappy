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
            Model getModel();
            Texture2D getTexture();
            Model getIQM();
    };
}
