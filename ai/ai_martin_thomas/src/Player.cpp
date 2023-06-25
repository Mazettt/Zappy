#include "Player.hpp"

using namespace my;

Player::Player(const Args &args):
    _s(args),
    _foodEaten(0)
{}

Player::Player(Player &&other):
    _s(std::move(other._s)),
    _elevcond(std::move(other._elevcond)),
    _foodEaten(other._foodEaten)
{
    other._foodEaten = 0;
}

Player::~Player() {}

Player &Player::operator=(Player &&other)
{
    _s = std::move(other._s);
    _elevcond = std::move(other._elevcond);
    _foodEaten = other._foodEaten;
    other._foodEaten = 0;
    return *this;
}

bool Player::canElevate()
{
    auto l = look();
    std::cout << "nbr player: " << l[0].getNbr(Resource::PLAYER) << std::endl;
    for (Resource i = Resource::LINEMATE; i != Resource::NONE; i = static_cast<Resource>(static_cast<int>(i) + 1))
        if (_elevcond.get(getLevel(), i) > l[0].getNbr(i)) {
            std::cout << "Incantation failed: need " << (_elevcond.get(getLevel(), i) - l[0].getNbr(i)) << " " << my::typeToString(i) << " more" << std::endl;
            return false;
        }
    if (this->getLevel() > 3 && _elevcond.get(getLevel(), Resource::PLAYER) > 6) {
        std::cout << "Incantation failed: need " << (_elevcond.get(getLevel(), Resource::PLAYER) - l[0].getNbr(Resource::PLAYER)) << " " << my::typeToString(Resource::PLAYER) << " more" << std::endl;
            return false;
    }
    return true;
}

const std::string &Player::getTeam() const
{
    return _s.getTeam();
}

const std::pair<int, int> &Player::getMapSize() const
{
    return _s.getMapSize();
}

int Player::getLevel() const
{
    return _s.getLvl();
}

void Player::lookForResource(Resource type)
{
    int begins[9] = {0, 1, 4, 9, 16, 25, 36, 49, 64};
    int ends[9] = {0, 3, 8, 15, 24, 35, 48, 63, 80};
    const auto &l = look();

    for (int i = 0; i <= getLevel(); ++i) {
        for (int j = begins[i]; j <= ends[i]; ++j) {
            if (l[j].getNbr(type)) {
                goToTile(j);
                take(type);
                return;
            }
        }
    }
    forward();
}

void Player::lookForResources(const std::unordered_map<my::Resource, int> &needs)
{
    const auto &tiles = look();

    int begins[9] = {0, 1, 4, 9, 16, 25, 36, 49, 64};
    int ends[9] = {0, 3, 8, 15, 24, 35, 48, 63, 80};
    std::unordered_map<int, int> tileValues;

    for (int i = 0; i <= this->getLevel(); ++i) {
        for (int j = begins[i]; j <= ends[i]; ++j) {
            for (const auto &need : needs) {
                int amount = std::min(need.second, tiles[j].getNbr(need.first));
                tileValues[j] += amount;
            }
        }
    }
    auto maxElementIt = std::max_element(
        tileValues.begin(),
        tileValues.end(),
        [](const auto &a, const auto &b) {
            return a.second < b.second;
        }
    );
    int maxIndex = maxElementIt->first;

    goToTile(maxIndex);
    int foodInTile = tiles[maxIndex].getNbr(Resource::FOOD);
    for (int i = 0; i < foodInTile; ++i) {
        take(Resource::FOOD);
    }
    for (const auto &need : needs) {
        int amountInTile = tiles[maxIndex].getNbr(need.first);
        int amountToTake = std::min(amountInTile, need.second);
        for (int i = 0; i < amountToTake; ++i) {
            take(need.first);
        }
    }
}


void Player::goToTile(int tileIndex)
{
    int begins[9] = {0, 1, 4, 9, 16, 25, 36, 49, 64};
    int middle[9] = {0, 2, 6, 12, 20, 30, 42, 56, 72};
    int ends[9] = {0, 3, 8, 15, 24, 35, 48, 63, 80};

    int line = 0;

    for (int i = 0; i < 9; i++) {
        if (tileIndex >= begins[i] && tileIndex <= ends[i]) {
            line = i;
            break;
        }
    }
    for (int i = 0; i < line; i++)
        forward();
    if (tileIndex < middle[line]) {
        left();
        for (int i = middle[line]; i > tileIndex; i--)
            forward();
    } else if (tileIndex > middle[line]) {
        right();
        for (int i = middle[line]; i < tileIndex; i++)
            forward();
    }
}

void Player::goToDirection(int direction)
{
    switch (direction) {
        case 0:
            break;
        case 1:
            forward();
            break;
        case 2:
            forward();
            left();
            forward();
            break;
        case 3:
            left();
            forward();
            break;
        case 4:
            left();
            forward();
            left();
            forward();
            break;
        case 5:
            left();
            left();
            forward();
            break;
        case 6:
            right();
            forward();
            right();
            forward();
            break;
        case 7:
            right();
            forward();
            break;
        case 8:
            forward();
            right();
            forward();
            break;
        default:
            break;
    }
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

std::vector<Tile> Player::look()
{
    return _s.look();
}

std::unordered_map<Resource, int> Player::inventory()
{
    return _s.inventory();
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
    return _s.take(type);
}

bool Player::set(Resource type)
{
    return _s.set(type);
}

int Player::incantation()
{
    if (canElevate()) {
        int newlvl = _s.incantation();
        if (newlvl != -1) {
            std::cout << "Incantation ok" << std::endl;
            return newlvl;
        }
    }
    return -1;
}

std::optional<std::pair<std::string, int>> Player::getBroadcast()
{
    return _s.getBroadcast();
}

void Player::clearBroadcast()
{
    _s.clearBroadcast();
}
