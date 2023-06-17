/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Burger.hpp
*/

#pragma once
#include <string>
#include "IResource.hpp"

#include "../MyRayLibHeader/Draw.hpp"
#include "../MyRayLibHeader/Color.hpp"
#include "../MyRayLibHeader/Model.hpp"
#include "../MyRayLibHeader/Texture.hpp"
#include "../MyRayLibHeader/Vector3D.hpp"

namespace ZappyGui {
    class Burger: public IResource {
        private:
            MyRayLib::Vector3D _scale;
            float _rotationAngle;
            MyRayLib::Vector3D _position;
            const MyRayLib::Model &_model;
            const MyRayLib::Texture2D &_texture;
        public:
            Burger(const MyRayLib::Model &model, const MyRayLib::Texture2D &texture, const MyRayLib::Vector3D &position);
            ~Burger();
            virtual IResource::resourceType getType();
            virtual void setPosition(float x, float z);
            virtual const MyRayLib::Vector3D &getPosition();
            virtual void draw();
            virtual int getId() { return -1; }
    };
}
