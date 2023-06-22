/*
** EPITECH PROJECT, 2022
** cpp
** File description:
** FoodHandler.cpp
*/

#include <cmath>
#include <iostream>
#include "FoodHandler.hpp"

using namespace my;

FoodHandler::FoodHandler(int x, int y):
    _incantationScore(0),
    _mapSize(x, y),
    _factorLevel(0.5),
    _factorMapSize(0.03),
    _factorIncantationScore(0.64)
    {}

FoodHandler::~FoodHandler() {}

int FoodHandler::getMinimumFood() {
    return this->_minimumFood;
}

int FoodHandler::getMaximumFood() {
    return this->_maximumFood;
}

void FoodHandler::calculate(int playerLevel) {
    // MINIMUM PART
    double levelResult = playerLevel * this->_factorLevel;

    double incantationBase = (this->_incantationScore >= 0) ? this->_incantationScore : -1.0 / this->_incantationScore;
    double incantationResult = std::pow(incantationBase, -this->_factorIncantationScore);

    double mapResult = std::pow((this->_mapSize.first * this->_mapSize.second), this->_factorMapSize);

    int minimumFood = std::round(levelResult + incantationResult + mapResult);
    this->_minimumFood = ((minimumFood > 4) ? minimumFood : 4);


    // MAXIMUM PART
    double levelResult1 = playerLevel * this->_factorLevel;

    double incantationBase1 = (this->_incantationScore >= 0) ? this->_incantationScore : -1.0 / this->_incantationScore;
    double incantationResult1 = std::pow(incantationBase1, -this->_factorIncantationScore);

    double mapResult1 = std::pow((this->_mapSize.first * this->_mapSize.second), this->_factorMapSize);

    int maximumFood = std::round((levelResult1 + incantationResult1 + mapResult1) * 4);
    this->_maximumFood = ((maximumFood > 4 * 4) ? maximumFood : 4 * 4);

    // std::cout << "MINUMUM PART: " << levelResult << " " << incantationResult << " " << mapResult << " " << _minimumFood << " | MAXIMUM PART " << levelResult1 << " " << incantationResult1 << " " << mapResult1 << " " << _maximumFood << std::endl;
}

void FoodHandler::incantationFail() {
    this->_incantationScore += 1;
}

void FoodHandler::incantationSuccess() {
    this->_incantationScore -= 1;
}

int FoodHandler::getIncantationScore() {
    return this->_incantationScore;
}
