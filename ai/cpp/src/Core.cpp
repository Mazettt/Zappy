#include "Core.hpp"
#include <thread>

using namespace my;

Core::Core(const Args &args):
    _args(args),
    _player(args),
    _state(State::FIND_FOOD),
    _comingPlayers(0),
    _comingDir(1)
{}

Core::~Core() {}

void Core::run()
{
    // bool forked = false;

    // int count = -1;
    // int dir = -1;
    // int bestTile = -1;

    // for (int i = 0; i < 4; i++) {
    //     const auto &look = _player.look();
    //     for (int j = 0; j < 4; j++) {
    //         int countBuff = 0;
    //         for (Resource resource = Resource::PLAYER; resource != Resource::NONE; resource = static_cast<Resource>(static_cast<int>(resource) + 1)) {
    //             if (resource == Resource::PLAYER)
    //                 countBuff++;
    //             else if (look[j].getNbr(resource) >= _elevcond.get(_player.getLevel(), resource))
    //                 countBuff++;
    //         }
    //         if (countBuff > count || count == -1) {
    //             count = countBuff;
    //             dir = i;
    //             bestTile = j;
    //         }
    //     }
    //     _player.right();
    // }

    // for (int i = 0; i < dir; i++)
    //     _player.right();
    // if (bestTile == 1) {
    //     _player.forward();
    //     _player.left();
    //     _player.forward();
    // } else if (bestTile == 2) {
    //     _player.forward();
    // } else if (bestTile == 3) {
    //     _player.forward();
    //     _player.right();
    //     _player.forward();
    // }
    // if (_player.incantation() != -1)
    //     std::cout << "Incantation ok" << std::endl;
    // else
    //     std::cout << "Incantation failed" << std::endl;

    while (true) {
        std::map<my::Resource, int> inv = _player.inventory();
        if (inv.at(Resource::FOOD) < 5) {
            if (_state == State::TRY_INCANT)
                _player.broadcast("abort incantation");
            _state = State::FIND_FOOD;
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
        // std::cout << "Player food: " << _player.inventory().at(Resource::FOOD) << " | lvl: " << _player.getLevel() << " | coming: " << _comingPlayers << std::endl;
    }
}

void Core::_findFood(const std::map<my::Resource, int> &inventory)
{
    if (inventory.at(Resource::FOOD) >= 20) {
        _state = State::FIND_RESOURCES;
        return;
    }
    _player.lookForResource(Resource::FOOD);
}

void Core::_comeToIncantation(const std::map<my::Resource, int> &inventory)
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

void Core::_incant(const std::map<my::Resource, int> &inventory)
{
    const auto &look = _player.look();
    if (look[0].getNbr(Resource::PLAYER) >= _elevcond.get(_player.getLevel(), Resource::PLAYER)) {
        std::cout << "begin: " << look[0].getNbr(Resource::PLAYER) << std::endl;
        _player.broadcast("dir0: wait");
        std::cout << "incanting..." << std::endl;
        for (Resource i = Resource::LINEMATE; i != Resource::NONE; i = static_cast<Resource>(static_cast<int>(i) + 1)) {
            for (int it = look[0].getNbr(i); it < _elevcond.get(_player.getLevel(), i); it++)
                _player.set(i);
        }
        _player.incantation();
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
        std::cout << "Recieved broadcast1: " << msg->first << " | dir: " << msg->second << std::endl;
        if (msg->first == "abort incantation")
            _state = State::FIND_RESOURCES;
        else if (msg->first.find("can incant: lvl ") == 0 && std::stoi(msg->first.substr(16)) == _player.getLevel()) {
            if (_state != State::COME_TO_INCANTATION)
                _player.broadcast("coming");
            _comingDir = msg->second;
            _state = State::COME_TO_INCANTATION;
        } else if (msg->first == "coming" && _state == State::TRY_INCANT)
            _comingPlayers++;
        else if (msg->first == "dir0: wait" && msg->second == 0) {
            std::cout << "Waiting for incantation" << std::endl;
            while (true) {
                _player.inventory();
                std::optional<std::pair<std::string, int>> msg = _player.getBroadcast();
                if (msg && msg->first == "dir0: incantation done" && msg->second == 0) {
                    _state = State::FIND_RESOURCES;
                    std::cout << "Current lvl: " << _player.getLevel() << std::endl;
                    break;
                } else if (msg) {
                    std::cout << "Recieved broadcast2: " << msg->first << " | dir: " << msg->second << std::endl;
                }
                if (_player.inventory().at(Resource::FOOD) < 5) {
                    _state = State::FIND_RESOURCES;
                    break;
                }
            }
        }

        msg = _player.getBroadcast();
    }
}

void Core::_fork() {
    _player.fork();
    _childs.push_back(Player(_args));
}
