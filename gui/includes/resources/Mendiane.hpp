/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Mendiane.hpp
*/

#pragma once
#include <string>
#include "IResource.hpp"

#include "../MyRayLibHeader/Draw.hpp"
#include "../MyRayLibHeader/Color.hpp"
#include "../MyRayLibHeader/Model.hpp"
#include "../MyRayLibHeader/Texture.hpp"

namespace ZappyGui {
    class Mendiane: public IResource {
        private:
            Vector3 _scale;
            float _rotationAngle;
            Vector3 _position;
            MyRayLib::Model _model;
            MyRayLib::Texture2D _texture;
        public:
            Mendiane();
            ~Mendiane();
            void setPosition(float x, float z);
            Vector3 getPosition();
            void draw();
    };
}
