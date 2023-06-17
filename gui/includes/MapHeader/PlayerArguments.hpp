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
#include "Player.hpp"

namespace ZappyGui {
    class PlayerArguments {
        private:
            int _playerLevel;
            int _playerNumber;
            std::string _teamName;
            MyRayLib::Vector3D _position;

            MyRayLib::Vector3D _orientationAxis;
            float _rotationAngle;
            MyRayLib::Vector3D _scale;
            int _animationFrameCounter;
            int _animationType;

        public:
            PlayerArguments(): _playerLevel(0), _playerNumber(0), _teamName(""), _position({0.0, 0.0, 0.0}), _orientationAxis({0.0, 0.0, 0.0}), _rotationAngle(0.0), _scale({0.0, 0.0, 0.0}), _animationFrameCounter(0), _animationType(0) {};
            PlayerArguments(MyRayLib::Vector3D position, MyRayLib::Vector3D orientationAxis, float rotationAngle, MyRayLib::Vector3D scale): _playerLevel(0), _playerNumber(0), _teamName(""), _position(position), _orientationAxis(orientationAxis), _rotationAngle(rotationAngle), _scale(scale), _animationFrameCounter(0), _animationType(0) {};
            PlayerArguments(int playerNumber, std::string teamName, MyRayLib::Vector3D position, MyRayLib::Vector3D orientationAxis, float rotationAngle, MyRayLib::Vector3D scale, int animationFrameCounter, int playerArgs):
                _playerLevel(1), _playerNumber(playerNumber), _teamName(teamName), _position(position), _orientationAxis(orientationAxis), _rotationAngle(rotationAngle), _scale(scale), _animationFrameCounter(animationFrameCounter), _animationType(playerArgs) {
            };
            PlayerArguments(const PlayerArguments &playerArgs) {
            this->_playerLevel = playerArgs.getPlayerLevel();
            this->_playerNumber = playerArgs.getPlayerNumber();
            this->_teamName = playerArgs.getTeamName();
            this->_position = playerArgs.getPosition();
            this->_orientationAxis = playerArgs.getOrientationAxis();
            this->_rotationAngle = playerArgs.getRotationAngle();
            this->_scale = playerArgs.getScale();
            this->_animationFrameCounter = playerArgs.getAnimationFrameCounter();
            this->_animationType = playerArgs.getAnimationType();
            };
            ~PlayerArguments() {};
            int getAnimationType() const {
                return _animationType;
            }
            int getPlayerLevel() const {
                return _playerLevel;
            }
            int getPlayerNumber() const {
                return _playerNumber;
            }
            std::string getTeamName() const {
                return _teamName;
            }
            MyRayLib::Vector3D getOrientationAxis() const {
                return _orientationAxis;
            }
            float getRotationAngle() const {

                return _rotationAngle;
            }
            MyRayLib::Vector3D getScale() const {
                return _scale;
            }
            MyRayLib::Vector3D getPosition() const {
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
            void setOrientationAxis(MyRayLib::Vector3D orientationAxis) {
                _orientationAxis = orientationAxis;
            }
            void setRotationAngle(float rotationAngle) {
                _rotationAngle = rotationAngle;
            }
            void setScale(MyRayLib::Vector3D scale) {
                _scale = scale;
            }
            void setPosition(MyRayLib::Vector3D position) {
                _position = position;
            }
            void setAnimationFrameCounter(int animationFrameCounter) {
                _animationFrameCounter = animationFrameCounter;
            }
            void setAnimationType(int type) {
                _animationType = type;
            }
    };
}