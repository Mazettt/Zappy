/*
** EPITECH PROJECT, 2022
** cpp
** File description:
** ForkHandler.cpp
*/

#include "ForkHandler.hpp"

using namespace my;

ForkHandler::ForkHandler():
    _failIncantationCounter(0),
    _teamMaximumSize(0),
    _teamFreeSlots(0),
    _thresholdDecision(0.6),
    _weightLevel(0.4),
    _weightFails(0.6),
    _weightSlots(0.1),
    _decision(false)
    {}

ForkHandler::~ForkHandler() {}

void ForkHandler::calculate(int playerLevel, int teamMaximumSize, int teamFreeSlots) {
    this->_teamMaximumSize = teamMaximumSize;
    this->_teamFreeSlots = teamFreeSlots;

    double normalizedLevel = playerLevel / 8;
    double normalizedFails = this->_failIncantationCounter / 10;
    double normalizedSlots = this->_teamFreeSlots / this->_teamMaximumSize;

    double thresholdFork = (this->_weightLevel * normalizedLevel) + (this->_weightFails * normalizedFails) + (this->_weightSlots * normalizedSlots);
    this->_decision = (thresholdFork > this->_thresholdDecision) ? true : false;
}

bool ForkHandler::getForkDecision() {
    return this->_decision;
}
