/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Food.hpp
*/

#pragma once
#include <string>
#include "IResource.hpp"

#include "../MyRayLibHeader/Draw.hpp"
#include "../MyRayLibHeader/Color.hpp"
#include "../MyRayLibHeader/Model.hpp"
#include "../MyRayLibHeader/Texture.hpp"

namespace ZappyGui {
    class Food: public IResource {
        private:
            Vector3 _orientationAxis;
            float _rotationAngle;
            Vector3 _scale;
            Vector3 _position;
            MyRayLib::Model _model;
            MyRayLib::Texture2D _texture;
        public:
            Food();
            ~Food();
            void setPosition(int x, int y);
            void draw();
    };
}
