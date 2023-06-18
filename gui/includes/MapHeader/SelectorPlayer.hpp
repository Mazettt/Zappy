/*
** EPITECH PROJECT, 2022
** gui
** File description:
** SelectorPlayer.hpp
*/

#pragma once
#include <string>
#include <unordered_map>
#include "../MyRayLibHeader/Model.hpp"
#include "../MyRayLibHeader/AnimationsModel.hpp"
#include "../MyRayLibHeader/Color.hpp"
#include "../MyRayLibHeader/Draw.hpp"
#include "../MyRayLibHeader/Vector3D.hpp"
#include "../resources/IResource.hpp"

namespace ZappyGui {
    class SelectorPlayer {
        private:
            MyRayLib::Vector3D _pos;
            MyRayLib::Model &_model;
            MyRayLib::AnimationsModel &_animation;
            int _frameCounterAnimation;

        public:
            SelectorPlayer(MyRayLib::Model &model, MyRayLib::AnimationsModel &animation);
            ~SelectorPlayer() {};
            void setPosition(const MyRayLib::Vector3D &pos);
            const MyRayLib::Vector3D getPosition() const;
            void update();
            void draw();
    };
}
