#include "Core.hpp"

using namespace my;

Core::Core(const Args &args):
    _s(args),
    _foodEaten(0)
{}

Core::~Core() {}

void Core::run()
{
    while (true) {
        auto look = _s.look();

        if (_isResourceInTile(look[0], Resource::FOOD)) {
            if (_s.take(Resource::FOOD))
                ++_foodEaten;
        } else if (_isResourceInTile(look[2], Resource::FOOD)) {
            _s.forward();
            if (_s.take(Resource::FOOD))
                ++_foodEaten;
        } else if (_isResourceInTile(look[1], Resource::FOOD)) {
            _s.forward();
            _s.left();
            _s.forward();
            if (_s.take(Resource::FOOD))
                ++_foodEaten;
        } else if (_isResourceInTile(look[3], Resource::FOOD)) {
            _s.forward();
            _s.right();
            _s.forward();
            if (_s.take(Resource::FOOD))
                ++_foodEaten;
        } else
            _s.forward();

        auto oui = _s.inventory();
        std::cout << "Food eaten: " << _foodEaten << " | Food left: " << oui[Resource::FOOD] << " Message: " << _s.getBroadcast().value_or("") << "\r"  << std::flush;
    }
}

bool Core::_isResourceInTile(const std::vector<Resource> &tile, Resource type) const
{
    return std::find(tile.begin(), tile.end(), type) != tile.end();
}
