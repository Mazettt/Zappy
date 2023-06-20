#include "Core.hpp"

using namespace my;

Core::Core(const Args &args):
    _args(args),
    _player(args)
{}

Core::~Core() {}

void Core::run()
{
    bool forked = false;
    while (true) {
        auto oui = _player.inventory();
        if (!forked && oui[Resource::FOOD] >= 15) {
            _fork();
            forked = true;
        }

        _lookForFood(_player);
        std::cout << "Player food: " << _player.inventory().at(Resource::FOOD) << std::endl;
        for (auto &i : _childs) {
            _lookForFood(i);
            std::cout << "Child food: " << i.inventory().at(Resource::FOOD) << std::endl;
        }
    }
}

void Core::_fork() {
    _player.fork();
    _childs.push_back(Player(_args));
}

void Core::_lookForFood(Player &player)
{
    const auto &look = player.look();

    if (look[0].getNbr(Resource::FOOD))
        player.take(Resource::FOOD);
    else if (look[2].getNbr(Resource::FOOD)) {
        player.forward();
        player.take(Resource::FOOD);
    } else if (look[1].getNbr(Resource::FOOD)) {
        player.forward();
        player.left();
        player.forward();
        player.take(Resource::FOOD);
    } else if (look[3].getNbr(Resource::FOOD)) {
        player.forward();
        player.right();
        player.forward();
        player.take(Resource::FOOD);
    } else
        player.forward();
}