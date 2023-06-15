/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Thystame.hpp
*/

#pragma once
#include <string>
#include "IResource.hpp"

#include "../MyRayLibHeader/Draw.hpp"
#include "../MyRayLibHeader/Color.hpp"
#include "../MyRayLibHeader/Model.hpp"
#include "../MyRayLibHeader/Texture.hpp"

namespace ZappyGui {
    class Thystame: public IResource {
        private:
            Vector3 _scale;
            float _rotationAngle;
            Vector3 _position;
            const MyRayLib::Model &_model;
            const MyRayLib::Texture2D &_texture;
        public:
            Thystame(const MyRayLib::Model &model, const MyRayLib::Texture2D &texture, const Vector3 &position);
            ~Thystame();
            virtual IResource::resourceType getType();
            virtual void setPosition(float x, float z);
            virtual const Vector3 &getPosition();
            virtual void draw();
            virtual int getId() { return -1; }
    };
}
