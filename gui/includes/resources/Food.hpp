/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Food.hpp
*/

#pragma once
#include <string>
#include "IResource.hpp"

namespace ZappyGui {
    class Food: public IResource {
        private:
            Model _model;
            Texture2D _texture;
        public:
            Food(const std::string &modelPath, const std::string &texturePath);
            ~Food();
            Model getModel();
            Texture2D getTexture();
    };
}
