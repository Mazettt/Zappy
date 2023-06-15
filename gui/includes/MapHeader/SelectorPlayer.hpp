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
#include "../resources/IResource.hpp"

namespace ZappyGui {
    class SelectorPlayer {
        private:
            Vector3 _pos;
            MyRayLib::Model &_model;
            MyRayLib::AnimationsModel &_animation;
            int _frameCounterAnimation;
            int _animationCounter;

        public:
            SelectorPlayer(MyRayLib::Model &model, MyRayLib::AnimationsModel &animation);
            ~SelectorPlayer() {};
            void setPosition(const Vector3 &pos);
            const Vector3 getPosition() const;
            void update();
            void draw();
    };
}
