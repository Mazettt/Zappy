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

        if (look[0].getNbr(Resource::FOOD)) {
            if (_s.take(Resource::FOOD))
                ++_foodEaten;
        } else if (look[2].getNbr(Resource::FOOD)) {
            _s.forward();
            if (_s.take(Resource::FOOD))
                ++_foodEaten;
        } else if (look[1].getNbr(Resource::FOOD)) {
            _s.forward();
            _s.left();
            _s.forward();
            if (_s.take(Resource::FOOD))
                ++_foodEaten;
        } else if (look[3].getNbr(Resource::FOOD)) {
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
