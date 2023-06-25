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
    _comingDir(1),
    _levelResponses(0),
    hasReceivedCheck(false),
    hasRequestedCheck(false),
    check(true)
{}

Core::~Core() {}

void Core::run()
{
    while (true) {
        this->_foodHandler.calculate(this->_player.getLevel());
        std::unordered_map <my::Resource, int> inv = _player.inventory();
        if (inv.at(Resource::FOOD) <= this->_foodHandler.getMinimumFood()) {
            if (_state == State::TRY_INCANT) {
                std::cout << "Incantation abort" << std::endl;
                _player.broadcast("abort incantation");
                this->_foodHandler.incantationFail();
                if (this->_player.getLevel() < 5) _fork();
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
        checkResponses();
    }
}

void Core::_findFood(const std::unordered_map <my::Resource, int> &inventory)
{
    if (inventory.at(Resource::FOOD) >= this->_foodHandler.getMaximumFood()) {
        _state = State::FIND_RESOURCES;
        return;
    }
    _player.lookForResource(Resource::FOOD);
}

void Core::_comeToIncantation(unused const std::unordered_map <my::Resource, int> &inventory)
{
    if (_comingDir > 0) {
        _player.goToDirection(_comingDir);
        _comingDir = 0;
        _player.clearBroadcast();
    }
}

void Core::_findResources(const std::unordered_map<my::Resource, int> &inventory)
{
    if (inventory.at(Resource::FOOD) < this->_foodHandler.getMaximumFood()) {
        _player.lookForResource(Resource::FOOD);
        return;
    }
    std::unordered_map<my::Resource, int> resourceNeeds;
    for (Resource i = Resource::LINEMATE; i != Resource::NONE; i = static_cast<Resource>(static_cast<int>(i) + 1)) {
        int required = _elevcond.get(_player.getLevel(), i) - inventory.at(i);
        if (required > 0 || (i == Resource::THYSTAME && inventory.at(i) == 0)) {
            resourceNeeds[i] = required + 1;
        }
    }

    if (resourceNeeds.empty()) {
        this->_comingPlayers = 0;
        this->_state = State::TRY_INCANT;
        return;
    }

    _player.lookForResources(resourceNeeds);
}

void Core::_incant(unused const std::unordered_map <my::Resource, int> &inventory)
{
    const auto &look = _player.look();
    if (look[0].getNbr(Resource::PLAYER) >= _elevcond.get(_player.getLevel(), Resource::PLAYER)) {
        _player.broadcast("dir0: wait");
        for (Resource i = Resource::LINEMATE; i != Resource::NONE; i = static_cast<Resource>(static_cast<int>(i) + 1)) {
            for (int it = look[0].getNbr(i); it < _elevcond.get(_player.getLevel(), i); it++)
                _player.set(i);
        }
        if (_player.getLevel() == 2 && !hasRequestedCheck && !hasReceivedCheck && _levelResponses == 0) {
            _player.broadcast("presence check");
            _broadcastTime = std::chrono::system_clock::now();
            hasRequestedCheck = true;
        }
        if (_player.incantation() == -1) {
            this->_forkHandler.incantationFailed();
        } else {
            this->_forkHandler.incantationSuccess();
            this->_foodHandler.incantationSuccess();
        }
        std::cout << "Current lvl: " << _player.getLevel() << std::endl;
        _player.broadcast("dir0: incantation done");
        _state = State::FIND_FOOD;
        _player.eject();
    } else
        _player.broadcast(std::string("can incant: lvl ") + std::to_string(_player.getLevel()));
}

void Core::_handleBroadcast()
{
    std::optional<std::pair<std::string, int>> msg = _player.getBroadcast();
    while (msg) {
        if (msg->first == "abort incantation")
            _state = State::FIND_FOOD;
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
                    _state = State::FIND_FOOD;
                    return true;
                }
                return false;
            });
        } else if (msg->first == "presence check") {
            _player.broadcast("Im here");
            std::cout << "AAAAH: " << _player.getLevel() << std::endl;
            hasReceivedCheck = true;
        } else if (msg->first == "Im here") {
            _levelResponses += 1;
        }

        msg = _player.getBroadcast();
    }
}

void Core::checkResponses() {
  auto now = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = now - _broadcastTime;
  if (check == true && elapsed_seconds.count() >= 5.0 && hasReceivedCheck == false && hasRequestedCheck == true) {
    std::cout << "sdfgyhujhgfdfg " << elapsed_seconds.count()<< " " << _levelResponses << std::endl;
    int count = _levelResponses;
    if (count < 8) {
        _fork();
        _fork();
        _fork();
        _fork();

    }
    check = false;
  }
}


void Core::_waitBroadcast(const std::string &toFind, std::function<bool (std::pair<std::string, int>)> callback) {
    while (true) {
        std::unordered_map <my::Resource, int> inv = _player.inventory();
        if (inv.at(Resource::FOOD) < this->_foodHandler.getMinimumFood()) {
            _state = State::FIND_FOOD;
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
        std::cout << "FORK" << std::endl;
        tryRun(this->_args);
        exit(0);
    }
}
