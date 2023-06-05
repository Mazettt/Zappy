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
            const MyRayLib::Model &_model;
            const MyRayLib::Texture2D &_texture;
        public:
            Mendiane(const MyRayLib::Model &model, const MyRayLib::Texture2D &texture, const Vector3 &position);
            ~Mendiane();
            IResource::resourceType getType();
            void setPosition(float x, float z);
            const Vector3 &getPosition();
            void draw();
    };
}
