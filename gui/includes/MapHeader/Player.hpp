/*
** EPITECH PROJECT, 2022
** zappy
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
            MyRayLib::Vector3D move(float deltaTime, int timeUnit);
            bool updateAnimation(MyRayLib::Vector3D newPos);

        public:
            enum animationPlayerType {
                PLAYER_WIN,
                PLAYER_LVLUP,
                PLAYER_DIE,
                PLAYER_GET,
                PLAYER_WAIT,
                PLAYER_WALK,
                PLAYER_EXPULSION,
                PLAYER_NOTHING = 9
            };
            enum orientationAxis {
                NORTH = 180,
                EAST = 90,
                SOUTH = 0,
                WEST = 270
            };

            MyRayLib::Vector3D _movePos;
            Player(const PlayerArguments &playerArgs, MyRayLib::Model &model, const MyRayLib::Texture2D &texture, MyRayLib::AnimationsModel &animation);
            void addOnInventory(IResource::resourceType type, int quantity);
            bool removeOnInventory(IResource::resourceType type, int quantity);
            const std::unordered_map<IResource::resourceType, int> &getInventory() const;
            void animationWin();
            void animationLVLUP();
            void animationDie();
            void animationGet();
            void animationWait();
            void animationWalk();
            void animationExpulsion();
            void noAnimation();
            void draw();
            bool update(float deltaTime, int timeUnit);
            void setInventory(int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame);
            ~Player() {};
    };
}
