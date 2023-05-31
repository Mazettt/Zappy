/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Player.hpp
*/

#pragma once
#include "raylib.h"
#include <string>

namespace ZappyGui {
    class Player {
        private:
            bool _frozen;
            int _playerLevel;
            int _playerNumber;
            std::string _teamName;
            Vector3 _orientation;
            Vector2 _position;
            Model _model;
            Texture2D _texture;
            ModelAnimation _animation;
        public:
            Player(int playerNumber, Vector2 position, Vector3 orientation, int playerLevel, const std::string &teamName);
            void setDesign(const std::string &modelPath, const std::string &texturePath, const std::string &animationPath);
            void move(Vector2 position);
            void upgrade(int level);
            void inventory();
            ~Player() {};
    };
}
