#include "Player.hpp"

using namespace my;

Player::Player(const Args &args):
    _s(args),
    _foodEaten(0),
    _lvl(1),
    _inventoryUpdated(true)
{}

Player::Player(Player &&other):
    _s(std::move(other._s)),
    _elevcond(std::move(other._elevcond)),
    _inventory(std::move(other._inventory)),
    _lastLook(std::move(other._lastLook)),
    _foodEaten(other._foodEaten),
    _lvl(other._lvl),
    _inventoryUpdated(other._inventoryUpdated)
{
    other._foodEaten = 0;
    other._lvl = 1;
    other._inventoryUpdated = false;
}

Player::~Player() {}

Player &Player::operator=(Player &&other)
{
    _s = std::move(other._s);
    _elevcond = std::move(other._elevcond);
    _inventory = std::move(other._inventory);
    _lastLook = std::move(other._lastLook);
    _foodEaten = other._foodEaten;
    _lvl = other._lvl;
    _inventoryUpdated = other._inventoryUpdated;
    other._foodEaten = 0;
    other._lvl = 1;
    other._inventoryUpdated = false;
    return *this;
}

bool Player::canElevate()
{
    look();
    for (Resource i = Resource::FOOD; i != Resource::NONE; i = static_cast<Resource>(static_cast<int>(i) + 1)) {
        if (_elevcond.get(_lvl, i) > _lastLook[0].getNbr(i))
            return false;
    }
    return true;
}

void Player::forward()
{
    _s.forward();
}

void Player::left()
{
    _s.left();
}

void Player::right()
{
    _s.right();
}

const std::vector<Tile> &Player::look()
{
    _lastLook = _s.look();
    return _lastLook;
}

const std::map<Resource, int> &Player::inventory()
{
    if (_inventoryUpdated)
        _inventory = _s.inventory();
    _inventoryUpdated = false;
    return _inventory;
}

void Player::broadcast(const std::string &message)
{
    _s.broadcast(message);
}

int Player::connectNbr()
{
    return _s.connectNbr();
}

void Player::fork()
{
    _s.fork();
}

bool Player::eject()
{
    return _s.eject();
}

bool Player::take(Resource type)
{
    _inventoryUpdated = true;
    return _s.take(type);
}

bool Player::set(Resource type)
{
    _inventoryUpdated = true;
    return _s.set(type);
}

int Player::incantation()
{
    if (canElevate()) {
        int newlvl = _s.incantation();
        if (newlvl != -1) {
            _lvl = newlvl;
            return _lvl;
        }
    }
    return -1;
}
