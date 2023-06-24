#include "Tile.hpp"

using namespace my;

Tile::Tile()
{
    _fillEmpty();
}

Tile::Tile(const std::vector<Resource> &resources)
{
    for (auto &resource : resources)
        _resources[resource] += 1;
    _fillEmpty();
}

Tile::Tile(const std::unordered_map<Resource, int> &resources):
    _resources(resources)
{
    _fillEmpty();
}

Tile::Tile(const Tile &other):
    _resources(other._resources)
{}

Tile::Tile(Tile &&other):
    _resources(std::move(other._resources))
{}

Tile::~Tile() {}

Tile &Tile::operator=(const Tile &other)
{
    _resources = other._resources;
    return *this;
}

Tile &Tile::operator=(Tile &&other)
{
    _resources = std::move(other._resources);
    return *this;
}

void Tile::addResource(Resource type)
{
    _resources[type] += 1;
}

int Tile::getNbr(Resource type) const
{
    return _resources.at(type);
}

void Tile::_fillEmpty()
{
    for (Resource r = Resource::PLAYER; r < Resource::NONE; r = static_cast<Resource>(static_cast<int>(r) + 1))
        if (_resources.find(r) == _resources.end())
            _resources[r] = 0;
}
