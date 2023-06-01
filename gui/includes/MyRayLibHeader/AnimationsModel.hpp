/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** AnimationsModel.hpp
*/

#pragma once

#include <iostream>
#include "raylib.h"

namespace MyRayLib {
    class AnimationsModel {
        private:
            ::ModelAnimation *_animation;
            unsigned int _frameCount;
        public:
            AnimationsModel(const std::string &path) {
                _frameCount = 0;
                _animation = LoadModelAnimations(path.c_str(), &_frameCount);
            }
            ~AnimationsModel() {
                UnloadModelAnimations(_animation, _frameCount);
            }
            void MyUpdateModelAnimation(::Model model, int typeAnimation , int frame) {
                UpdateModelAnimation(model, _animation[typeAnimation], frame);
            }
            unsigned int getFrameCount() const {
                return _frameCount;
            }
            void setFrameCount(unsigned int frameCount) {
                _frameCount = frameCount;
            }
        };
}
