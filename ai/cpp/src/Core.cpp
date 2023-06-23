/*
** EPITECH PROJECT, 2022
** cpp
** File description:
** Core.cpp
*/

#include "Core.hpp"
#include <thread>

#define unused __attribute__((unused))
using namespace my;

Core::Core(const Args &args):
    _args(args),
    _player(args),
    _foodHandler(_player.getMapSize().first, _player.getMapSize().second),
    _forkHandler(),
    _state(State::FIND_FOOD),
    _comingPlayers(0),
    _comingDir(1)
{}

Core::~Core() {}

void Core::run()
{
    while (true) {
        this->_foodHandler.calculate(this->_player.getLevel());
        std::map<my::Resource, int> inv = _player.inventory();
        if (inv.at(Resource::FOOD) <= this->_foodHandler.getMinimumFood()) {
            if (_state == State::TRY_INCANT) {
                std::cout << "Incantation abort" << std::endl;
                _player.broadcast("abort incantation");
                this->_foodHandler.incantationFail();
                _fork();
            }
            _state = State::FIND_FOOD;
            std::cout << "Need food: " << inv.at(Resource::FOOD) << " minimumFood (" << this->_foodHandler.getMinimumFood() << ") maximumFood (" << this->_foodHandler.getMaximumFood() << ") playerLevel (" << this->_player.getLevel() << ")" << std::endl;
        }

        if (_state == State::FIND_FOOD)
            _findFood(inv);
        else if (_state == State::COME_TO_INCANTATION)
            _comeToIncantation(inv);
        else if (_state == State::FIND_RESOURCES)
            _findResources(inv);
        else if (_state == State::TRY_INCANT)
            _incant(inv);
        _handleBroadcast();
    }
}

void Core::_findFood(const std::map<my::Resource, int> &inventory)
{
    if (inventory.at(Resource::FOOD) >= this->_foodHandler.getMaximumFood()) {
        _state = State::FIND_RESOURCES;
        return;
    }
    _player.lookForResource(Resource::FOOD);
}

void Core::_comeToIncantation(unused const std::map<my::Resource, int> &inventory)
{
    if (_comingDir > 0) {
        _player.goToDirection(_comingDir);
        _comingDir = 0;
        _player.clearBroadcast();
    }
}

void Core::_findResources(const std::map<my::Resource, int> &inventory)
{
    for (Resource i = Resource::LINEMATE; i != Resource::NONE; i = static_cast<Resource>(static_cast<int>(i) + 1)) {
        if (inventory.at(i) < _elevcond.get(_player.getLevel(), i)) {
            _player.lookForResource(i);
            return;
        }
    }
    _comingPlayers = 0;
    _state = State::TRY_INCANT;
}

void Core::_incant(unused const std::map<my::Resource, int> &inventory)
{
    const auto &look = _player.look();
    if (look[0].getNbr(Resource::PLAYER) >= _elevcond.get(_player.getLevel(), Resource::PLAYER)) {
        _player.broadcast("dir0: wait");
        // std::cout << "Incanting..." << std::endl;
        for (Resource i = Resource::LINEMATE; i != Resource::NONE; i = static_cast<Resource>(static_cast<int>(i) + 1)) {
            for (int it = look[0].getNbr(i); it < _elevcond.get(_player.getLevel(), i); it++)
                _player.set(i);
        }
        if (_player.incantation() == -1) {
            this->_forkHandler.incantationFailed();
        } else {
            this->_forkHandler.incantationSuccess();
            this->_foodHandler.incantationSuccess();
        }
        std::cout << "Current lvl: " << _player.getLevel() << std::endl;
        _player.broadcast("dir0: incantation done");
        _state = State::FIND_RESOURCES;
        // _player.eject();
    } else
        _player.broadcast(std::string("can incant: lvl ") + std::to_string(_player.getLevel()));
}

void Core::_handleBroadcast()
{
    std::optional<std::pair<std::string, int>> msg = _player.getBroadcast();
    while (msg) {
        // std::cout << "Recieved broadcast1: " << msg->first << " | dir: " << msg->second << std::endl;
        if (msg->first == "abort incantation")
            _state = State::FIND_RESOURCES;
        else if (_state != FIND_FOOD && msg->first.find("can incant: lvl ") == 0 && std::stoi(msg->first.substr(16)) == _player.getLevel()) {
            if (_state != State::COME_TO_INCANTATION)
                _player.broadcast("coming");
            _comingDir = msg->second;
            _state = State::COME_TO_INCANTATION;
        } else if (msg->first == "coming" && _state == State::TRY_INCANT)
            _comingPlayers++;
        else if (msg->first == "dir0: wait" && msg->second == 0) {
            _waitBroadcast("dir0: incantation done", [this](std::pair<std::string, int> msg){
                if (msg.second == 0) {
                    _state = State::FIND_RESOURCES;
                    // std::cout << "Current lvl: " << _player.getLevel() << std::endl;
                    return true;
                }
                return false;
            });
        }

        msg = _player.getBroadcast();
    }
}

void Core::_waitBroadcast(const std::string &toFind, std::function<bool (std::pair<std::string, int>)> callback) {
    // std::cout << "Waiting for broadcast (" << toFind << ")" << std::endl;
    while (true) {
        std::map<my::Resource, int> inv = _player.inventory();
        if (inv.at(Resource::FOOD) < this->_foodHandler.getMinimumFood()) {
            _state = State::FIND_RESOURCES;
            break;
        }
        std::optional<std::pair<std::string, int>> msg = _player.getBroadcast();
        if (msg && msg->first.find(toFind) == 0)
            if (callback(*msg))
                break;
    }
}

void Core::_fork() {
    _player.fork();
    if (::fork() == 0) {
        tryRun(this->_args);
        exit(0);
    }
}
