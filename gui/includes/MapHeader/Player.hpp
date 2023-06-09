/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Player.hpp
*/

#pragma once
#include <string>
#include <unordered_map>
#include "PlayerArguments.hpp"
#include "../resources/IResource.hpp"

namespace ZappyGui {
    class Player: public PlayerArguments {
        private:
            MyRayLib::Model &_model;
            const MyRayLib::Texture2D &_texture;
            int _frameCounterAnimation;
            MyRayLib::AnimationsModel &_animation;
            std::unordered_map<IResource::resourceType, int> _inventory;

        public:
            int _animationCounter;
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
            void addOnInventory(IResource::resourceType type, int quantity);
            bool removeOnInventory(IResource::resourceType type, int quantity);
            const std::unordered_map<IResource::resourceType, int> getInventory() const;
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
