/*
** EPITECH PROJECT, 2022
** cpp
** File description:
** ForkHandler.cpp
*/

#include <cmath>
#include <iostream>
#include "ForkHandler.hpp"

using namespace my;

ForkHandler::ForkHandler():
    _failIncantationCounter(0),
    _thresholdDecision(0.62),
    _weightLevel(0.33),
    _weightFails(0.23),
    _decision(false)
    {}

ForkHandler::~ForkHandler() {}

void ForkHandler::calculate(int playerLevel) {
    double normalizedLevel = this->_weightLevel * std::exp(-0.06 * std::pow((playerLevel - 3.7), 2));
    double normalizedFails = this->_weightFails * std::exp(0.2 * this->_failIncantationCounter);
    double thresholdFork = std::round((normalizedLevel + normalizedFails) * 100) / 100;
    this->_decision = (thresholdFork >= this->_thresholdDecision) ? true : false;
}

bool ForkHandler::getForkDecision() {
    if (this->_decision == true)
        this->_failIncantationCounter = 0;
    return this->_decision;
}

void ForkHandler::incantationFailed() {
    this->_failIncantationCounter += 1;
}

void ForkHandler::incantationSuccess() {
    this->_failIncantationCounter = 0;
}