/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** Texture.hpp
*/

#pragma once

#include <iostream>
#include "raylib.h"

namespace MyRayLib {
    class Texture2D {
        private:
            ::Texture2D _texture;
        public:
            Texture2D() : _texture() {}
            Texture2D(const std::string &path) {
                _texture = LoadTexture(path.c_str());
            }
            ~Texture2D() {
                UnloadTexture(_texture);
            }
            void MySetMaterialTexture(::Model model, int mapType) {
                SetMaterialTexture(&model.materials[0], mapType, _texture);
            }
            const ::Texture2D getTexture() const {
                return _texture;
            }
    };
}
