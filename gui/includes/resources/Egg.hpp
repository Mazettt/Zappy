/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Egg.hpp
*/

#pragma once
#include <string>
#include "IResource.hpp"

namespace ZappyGui {
    class Egg: public IResource {
        private:
            Model _model;
            Texture2D _texture;
        public:
            Egg(const std::string &modelPath, const std::string &texturePath);
            ~Egg();
            Model getModel();
            Texture2D getTexture();
    };
}
