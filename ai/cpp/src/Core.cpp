#include "Core.hpp"
#include <thread>

using namespace my;

Core::Core(const Args &args):
    _args(args),
    _player(args),
    _comingPlayers(0),
    _waitIncantation(false),
    _comingToIncantation(false),
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
        _handleBroadcast();
        std::map<my::Resource, int> inv = _player.inventory();
        if (inv.at(Resource::FOOD) < ((_waitIncantation || _comingToIncantation) ? 5 : 20)) {
            if (_waitIncantation) {
                _player.broadcast("abort incantation");
                _waitIncantation = false;
            }
            _player.lookForResource(Resource::FOOD);
        } else if (_comingToIncantation) {
            std::cout << "coming: " << _comingDir << std::endl;
            _player.goToDirection(_comingDir);
            _comingDir = 0;
        } else {
            bool check = false;
            for (Resource i = Resource::LINEMATE; i != Resource::NONE; i = static_cast<Resource>(static_cast<int>(i) + 1)) {
                if (inv.at(i) < _elevcond.get(_player.getLevel(), i)) {
                    _player.lookForResource(i);
                    check = true;
                    break;
                }
            }
            if (!check) {
                const auto &look = _player.look();
                if (look[0].getNbr(Resource::PLAYER) >= _elevcond.get(_player.getLevel(), Resource::PLAYER)) {
                    _player.broadcast("dir0: wait");
                    for (Resource i = Resource::LINEMATE; i != Resource::NONE; i = static_cast<Resource>(static_cast<int>(i) + 1)) {
                        if (look[0].getNbr(i) < _elevcond.get(_player.getLevel(), i))
                            _player.set(i);
                    }
                    _player.incantation();
                    _player.broadcast("dir0: incantation done");
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                } else {
                    if (!_waitIncantation)
                        _comingPlayers = 0;
                    _player.broadcast(std::string("can incant: lvl ") + std::to_string(_player.getLevel()));
                    _waitIncantation = true;
                }
            }
        }
        // std::cout << "Player food: " << _player.inventory().at(Resource::FOOD) << " | lvl: " << _player.getLevel() << " | coming: " << _comingPlayers << std::endl;
    }
}

void Core::_handleBroadcast()
{
    std::optional<std::pair<std::string, int>> msg = _player.getBroadcast();
    while (msg) {
        // std::cout << "Recieved broadcast: " << msg->first << std::endl;
        if (msg->first == "abort incantation")
            _comingToIncantation = false;
        else if (msg->first.find("can incant: lvl ") == 0 && std::stoi(msg->first.substr(16)) == _player.getLevel()) {
            if (!_comingToIncantation)
                _player.broadcast("coming");
            _comingDir = msg->second;
            _comingToIncantation = true;
        } else if (msg->first == "coming" && _waitIncantation)
            _comingPlayers++;
        else if (msg->first == "dir0: wait" && msg->second == 0) {
            std::cout << "Waiting for incantation" << std::endl;
            while (true) {
                std::optional<std::pair<std::string, int>> msg = _player.getBroadcast();
                if (msg && msg->first == "dir0: incantation done" && msg->second == 0) {
                    _comingToIncantation = false;
                    std::cout << "Not coming anymore" << std::endl;
                    break;
                } else if (msg) {
                    std::cout << "Recieved broadcast: " << msg->first << " " << msg->second << std::endl;
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
