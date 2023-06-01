/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Player.hpp
*/

#pragma once
#include <string>
#include "../MyRayLibHeader/AnimationsModel.hpp"
#include "../MyRayLibHeader/Color.hpp"
#include "../MyRayLibHeader/Draw.hpp"
#include "../MyRayLibHeader/Model.hpp"
#include "../MyRayLibHeader/Texture.hpp"
#include "../MyRayLibHeader/Vector3D.hpp"
#include "../MyRayLibHeader/Window.hpp"


namespace ZappyGui {
    class Player {
        private:
            bool _frozen;
            int _playerLevel;
            int _playerNumber;
            std::string _teamName;
            Vector3 _orientationAxis;
            float _rotationAngle;
            Vector3 _scale;
            Vector3 _position;
            MyRayLib::Model _skinModel;
            MyRayLib::Texture2D _skinTexture;

            int _animationFrameCounter;
            MyRayLib::AnimationsModel _animation;
        public:
            Player(int playerNumber, int playerLevel, const std::string &teamName, Vector3 position, Vector3 orientationAxis, float rotationAngle, Vector3 scale);
            void move(Vector3 position);
            void upgrade(int level);
            void inventory();
            void draw();
            ~Player() {};
    };
}