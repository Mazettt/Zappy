/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Sibur.hpp
*/

#pragma once
#include <string>
#include "IResource.hpp"

#include "../MyRayLibHeader/Draw.hpp"
#include "../MyRayLibHeader/Color.hpp"
#include "../MyRayLibHeader/Model.hpp"
#include "../MyRayLibHeader/Texture.hpp"

namespace ZappyGui {
    class Sibur: public IResource {
        private:
            Vector3 _scale;
            float _rotationAngle;
            Vector3 _position;
            MyRayLib::Model _model;
            MyRayLib::Texture2D _texture;
        public:
            Sibur();
            ~Sibur();
            void setPosition(int x, int y);
            void draw();
    };
}
