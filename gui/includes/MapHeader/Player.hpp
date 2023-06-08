/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Player.hpp
*/

#pragma once
#include <string>
// #include "../MyRayLibHeader/AnimationsModel.hpp"
// #include "../MyRayLibHeader/Color.hpp"
// #include "../MyRayLibHeader/Draw.hpp"
// #include "../MyRayLibHeader/Model.hpp"
// #include "../MyRayLibHeader/Texture.hpp"
// #include "../MyRayLibHeader/Vector3D.hpp"
// #include "../MyRayLibHeader/Window.hpp"
#include "PlayerArguments.hpp"

namespace ZappyGui {
    class Player: public PlayerArguments {
        private:
            MyRayLib::Model &_model;
            const MyRayLib::Texture2D &_texture;
            int _frameCounterAnimation;
            MyRayLib::AnimationsModel &_animation;

        public:
            int _dieCounter;
            Vector3 _movePos;
            enum animationPlayerType {
                PLAYER_WIN,
                PLAYER_LVLUP,
                PLAYER_DIE,
                PLAYER_GET,
                PLAYER_WAIT,
                PLAYER_WALK,
                PLAYER_NOTHING = 9
            };
            Player(const PlayerArguments &playerArgs, MyRayLib::Model &model, const MyRayLib::Texture2D &texture, MyRayLib::AnimationsModel &animation);
            void animationWin();
            void animationLVLUP();
            void animationDie();
            void animationGet();
            void animationWait();
            void animationWalk();
            void noAnimation();
            void draw();
            ~Player() {};
    };
}
