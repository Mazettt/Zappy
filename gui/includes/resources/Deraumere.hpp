/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Deraumere.hpp
*/

#pragma once
#include <string>
#include "IResource.hpp"

#include "../MyRayLibHeader/Draw.hpp"
#include "../MyRayLibHeader/Color.hpp"
#include "../MyRayLibHeader/Model.hpp"
#include "../MyRayLibHeader/Texture.hpp"

namespace ZappyGui {
    class Deraumere: public IResource {
        private:
            Vector3 _scale;
            float _rotationAngle;
            Vector3 _position;
            MyRayLib::Model _model;
            MyRayLib::Texture2D _texture;
        public:
            Deraumere();
            ~Deraumere();
            void setPosition(float x, float z);
            Vector3 getPosition();
            void draw();
    };
}
