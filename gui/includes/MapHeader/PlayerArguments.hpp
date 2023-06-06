/*
** EPITECH PROJECT, 2022
** gui
** File description:
** PlayerArguments.hpp
*/

#pragma once
#include "../MyRayLibHeader/AnimationsModel.hpp"
#include "../MyRayLibHeader/Color.hpp"
#include "../MyRayLibHeader/Draw.hpp"
#include "../MyRayLibHeader/Model.hpp"
#include "../MyRayLibHeader/Texture.hpp"
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
            PlayerArguments(): _playerLevel(0), _playerNumber(0), _teamName(""), _orientationAxis({0.0, 0.0, 0.0}), _rotationAngle(0.0), _scale({0.0, 0.0, 0.0}), _position({0.0, 0.0, 0.0}), _animationFrameCounter(0) {};
            PlayerArguments(int playerLevel, int playerNumber, std::string teamName, Vector3 orientationAxis, float rotationAngle, Vector3 scale, Vector3 position, int animationFrameCounter):
            _playerLevel(playerLevel), _playerNumber(playerNumber), _teamName(teamName), _orientationAxis(orientationAxis), _rotationAngle(rotationAngle), _scale(scale), _position(position), _animationFrameCounter(animationFrameCounter) {};
            PlayerArguments(const PlayerArguments &playerArgs) {
                this->_playerLevel = playerArgs._playerLevel;
                this->_playerNumber = playerArgs._playerNumber;
                this->_teamName = playerArgs._teamName;
                this->_orientationAxis = playerArgs._orientationAxis;
                this->_scale = playerArgs._scale;
                this->_position = playerArgs._position;
                this->_animationFrameCounter = playerArgs._animationFrameCounter;
            };
            ~PlayerArguments() {};
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