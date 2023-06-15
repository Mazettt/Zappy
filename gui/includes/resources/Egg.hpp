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
            Vector3 _scale;
            float _rotationAngle;
            Vector3 _position;
            const MyRayLib::Model &_model;
            const MyRayLib::Texture2D &_texture;
            int _id;
        public:
            Egg(const MyRayLib::Model &model, const MyRayLib::Texture2D &texture, const Vector3 &position, int id);
            ~Egg();
            virtual IResource::resourceType getType();
            virtual void setPosition(float x, float z);
            virtual const Vector3 &getPosition();
            virtual void draw();
            virtual int getId() { return _id; }
    };
}
