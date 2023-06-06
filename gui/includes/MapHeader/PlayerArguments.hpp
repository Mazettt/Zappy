/*
** EPITECH PROJECT, 2022
** gui
** File description:
** PlayerArguments.hpp
*/

#pragma once
// #include "../MyRayLibHeader/AnimationsModel.hpp"
#include "../MyRayLibHeader/Color.hpp"
#include "../MyRayLibHeader/Draw.hpp"
// #include "../MyRayLibHeader/Model.hpp"
// #include "../MyRayLibHeader/Texture.hpp"
#include "../MyRayLibHeader/Vector3D.hpp"
#include "../MyRayLibHeader/Window.hpp"

namespace ZappyGui {
    class PlayerArguments {
        private:
            int _playerLevel;
            int _playerNumber;
            std::string _teamName;
            Vector3 _orientationAxis;
            float _rotationAngle;
            Vector3 _scale;
            Vector3 _position;
            int _animationFrameCounter;

        public:
            PlayerArguments(int _playerLevel, int _playerNumber, std::string _teamName, Vector3 _orientationAxis, float _rotationAngle, Vector3 _scale, Vector3 _position, int _animationFrameCounter);
            ~PlayerArguments();
            int getPlayerLevel() const {
                return _playerLevel;
            }
            int getPlayerNumber() const {
                return _playerNumber;
            }
            std::string getTeamName() const {
                return _teamName;
            }
            Vector3 getOrientationAxis() const {
                return _orientationAxis;
            }
            float getRotationAngle() const {
                return _rotationAngle;
            }
            Vector3 getScale() const {
                return _scale;
            }
            Vector3 getPosition() const {
                return _position;
            }
            int getAnimationFrameCounter() const {
                return _animationFrameCounter;
            }
            void setPlayerLevel(int playerLevel) {
                _playerLevel = playerLevel;
            }
            void setPlayerNumber(int playerNumber) {
                _playerNumber = playerNumber;
            }
            void setTeamName(std::string teamName) {
                _teamName = teamName;
            }
            void setOrientationAxis(Vector3 orientationAxis) {
                _orientationAxis = orientationAxis;
            }
            void setRotationAngle(float rotationAngle) {
                _rotationAngle = rotationAngle;
            }
            void setScale(Vector3 scale) {
                _scale = scale;
            }
            void setPosition(Vector3 position) {
                _position = position;
            }
            void setAnimationFrameCounter(int animationFrameCounter) {
                _animationFrameCounter = animationFrameCounter;
            }
    };
}