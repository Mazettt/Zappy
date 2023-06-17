/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Egg.hpp
*/

#pragma once
#include <string>
#include "IResource.hpp"

#include "../MyRayLibHeader/Draw.hpp"
#include "../MyRayLibHeader/Color.hpp"
#include "../MyRayLibHeader/Model.hpp"
#include "../MyRayLibHeader/Texture.hpp"

namespace ZappyGui {
    class Egg: public IResource {
        private:
            MyRayLib::Vector3D _scale;
            float _rotationAngle;
            MyRayLib::Vector3D _position;
            const MyRayLib::Model &_model;
            const MyRayLib::Texture2D &_texture;
            int _id;
        public:
            Egg(const MyRayLib::Model &model, const MyRayLib::Texture2D &texture, const MyRayLib::Vector3D &position, int id);
            ~Egg();
            virtual IResource::resourceType getType();
            virtual void setPosition(float x, float z);
            virtual const MyRayLib::Vector3D &getPosition();
            virtual void draw();
            virtual int getId() { return _id; }
    };
}
