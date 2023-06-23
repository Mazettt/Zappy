#include "ServerLink.hpp"

using namespace my;

ServerLink::ServerLink(const Args &args):
    _socket(args.getFlagValue<std::string>("-h"),
    args.getFlagValue<int>("-p")),
    _lvl(1)
{
    if (_socket.read() != "WELCOME\n")
        throw Error("Wrong welcome message", "main");
    _team = args.getFlagValue<std::string>("-n");
    _socket.write(_team + "\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto response = my::split(_socket.read(), " \n");
    if (response[0] == "ko")
        throw Error("Wrong team " + _team);
    _mapSize = std::make_pair(std::stoi(response[1]), std::stoi(response[2]));
    std::cout << "nbr clients remaining: " << response[0] << std::endl;
    std::cout << "map: " << _mapSize.first << " " << _mapSize.second << std::endl;
}

ServerLink::ServerLink(ServerLink &&other):
    _socket(std::move(other._socket)),
    _team(std::move(other._team)),
    _mapSize(std::move(other._mapSize)),
    _broadcast(std::move(other._broadcast))
{}

ServerLink::~ServerLink() {}

ServerLink &ServerLink::operator=(ServerLink &&other) {
    _socket = std::move(other._socket);
    _team = std::move(other._team);
    _mapSize = std::move(other._mapSize);
    _broadcast = std::move(other._broadcast);
    return *this;
}

const std::string &ServerLink::getTeam() const {
    return _team;
}

const std::pair<int, int> &ServerLink::getMapSize() const {
    return _mapSize;
}

int ServerLink::getLvl() const {
    return _lvl;
}

void ServerLink::forward() {
    _socket.write("Forward\n");
    while (true) {
        auto responses = _read();
        for (auto &it : responses) {
            if (it == "ok")
                return;
        }
    }
}

void ServerLink::left() {
    _socket.write("Left\n");
    while (true) {
        auto responses = _read();
        for (auto &it : responses) {
            if (it == "ok")
                return;
        }
    }
}

void ServerLink::right() {
    _socket.write("Right\n");
    while (true) {
        auto responses = _read();
        for (auto &it : responses) {
            if (it == "ok")
                return;
        }
    }
}

std::vector<Tile> ServerLink::look() {
    _socket.write("Look\n");
    std::vector<std::string> responses;
    std::string response;
    bool ok = false;
    while (!ok) {
        responses = _read();
        for (auto &it : responses)
            if (it[0] == '[') {
                response = it.substr(1, it.size() - 2);
                ok = true;
                break;
            }
    }
    auto map = my::splitWithEmpty(response, ",");
    std::vector<Tile> res;
    for (auto &line: map) {
        Tile tmp;
        auto resources = my::split(line, " ");
        for (auto &resource: resources) {
            if (resource == "player")
                tmp.addResource(Resource::PLAYER);
            else if (resource == "food")
                tmp.addResource(Resource::FOOD);
            else if (resource == "linemate")
                tmp.addResource(Resource::LINEMATE);
            else if (resource == "deraumere")
                tmp.addResource(Resource::DERAUMERE);
            else if (resource == "sibur")
                tmp.addResource(Resource::SIBUR);
            else if (resource == "mendiane")
                tmp.addResource(Resource::MENDIANE);
            else if (resource == "phiras")
                tmp.addResource(Resource::PHIRAS);
            else if (resource == "thystame")
                tmp.addResource(Resource::THYSTAME);
            else
                tmp.addResource(Resource::NONE);
        }
        res.push_back(tmp);
    }
    return res;
}

std::map<Resource, int> ServerLink::inventory() {
    _socket.write("Inventory\n");
    std::vector<std::string> responses;
    std::string response;
    bool ok = false;
    while (!ok) {
        responses = _read();
        for (auto &it : responses)
            if (it[0] == '[') {
                response = it.substr(1, it.size() - 2);
                ok = true;
                break;
            }
    }
    auto map = my::split(response, ",");
    std::map<Resource, int> res;
    for (Resource i = Resource::PLAYER; i != Resource::NONE; i = static_cast<Resource>(static_cast<int>(i) + 1))
        res[i] = 0;
    for (auto &line: map) {
        auto resources = my::split(line, " ");
        if (resources[0] == "player")
            res[Resource::PLAYER] = std::stoi(resources[1]);
        else if (resources[0] == "food")
            res[Resource::FOOD] = std::stoi(resources[1]);
        else if (resources[0] == "linemate")
            res[Resource::LINEMATE] = std::stoi(resources[1]);
        else if (resources[0] == "deraumere")
            res[Resource::DERAUMERE] = std::stoi(resources[1]);
        else if (resources[0] == "sibur")
            res[Resource::SIBUR] = std::stoi(resources[1]);
        else if (resources[0] == "mendiane")
            res[Resource::MENDIANE] = std::stoi(resources[1]);
        else if (resources[0] == "phiras")
            res[Resource::PHIRAS] = std::stoi(resources[1]);
        else if (resources[0] == "thystame")
            res[Resource::THYSTAME] = std::stoi(resources[1]);
    }
    return res;
}

void ServerLink::broadcast(const std::string &message) {
    _socket.write("Broadcast " + message + "\n");
    while (true) {
        auto responses = _read();
        for (auto &it : responses) {
            if (it == "ok")
                return;
        }
    }
}

int ServerLink::connectNbr() {
    _socket.write("Connect_nbr\n");
    auto responses = _read();
    if (responses.size() != 1)
        throw Error("Wrong response", "ServerLink::connectNbr");
    return std::stoi(responses[0]);
}

void ServerLink::fork() {
    _socket.write("Fork\n");
    while (true) {
        auto responses = _read();
        for (auto &it : responses) {
            if (it == "ok")
                return;
        }
    }
}

bool ServerLink::eject() {
    _socket.write("Eject\n");
    while (true) {
        auto responses = _read();
        for (auto &it : responses)
            if (it == "ok")
                return true;
            else if (it == "ko")
                return false;
    }
    return false;
}

bool ServerLink::take(Resource type) {
    _socket.write("Take " + typeToString(type) + "\n");
    while (true) {
        auto responses = _read();
        for (auto &it : responses) {
            if (it == "ok")
                return true;
            else if (it == "ko")
                return false;
        }
    }
    return false;
}

bool ServerLink::set(Resource type) {
    _socket.write("Set " + typeToString(type) + "\n");
    while (true) {
        auto responses = _read();
        for (auto &it : responses)
            if (it == "ok")
                return true;
            else if (it == "ko")
                return false;
    }
    return false;
}

int ServerLink::incantation() {
    _socket.write("Incantation\n");
    _read();
    int backupLvl = _lvl;
    _read(true);
    if (_lvl == backupLvl + 1)
        return _lvl;
    return -1;
}

std::optional<std::pair<std::string, int>> ServerLink::getBroadcast() {
    if (_broadcast.empty())
        return std::nullopt;
    std::pair<std::string, int> res = _broadcast.front();
    _broadcast.pop();
    return res;
}

void ServerLink::clearBroadcast() {
    while (_broadcast.size() > 0) {
        _broadcast.pop();
    }
}

std::vector<std::string> ServerLink::_read(bool incantation) {
    std::vector<std::string> res;
    while (res.size() == 0) {
        std::string tmp;
        do {
            tmp += _socket.read();
        } while (tmp.back() != '\n');
        tmp = tmp.substr(0, tmp.size() - 1);
        auto tmpvect = my::split(tmp, "\n");
        for (auto it = tmpvect.begin(); it != tmpvect.end();) {
            if (it->find("message") == 0) {
                _setBroadcast(*it);
                it = tmpvect.erase(it);
                continue;
            } else if (it->find("Current level") == 0) {
                _lvl = std::stoi(it->substr(15));
                it = tmpvect.erase(it);
                if (incantation)
                    return tmpvect;
                continue;
            } else if (it->find("eject: ") == 0) {
                it = tmpvect.erase(it);
                continue;
            } else if (it->find("dead") == 0)
                throw Warning("Dead");
            ++it;
        }
        res.insert(res.end(), tmpvect.begin(), tmpvect.end());
    }
    return res;
}

void ServerLink::_setBroadcast(const std::string &command) {
    _broadcast.push(std::make_pair(command.substr(11), std::stoi(command.substr(8, 1))));
}
