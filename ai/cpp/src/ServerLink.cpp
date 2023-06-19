#include "ServerLink.hpp"

using namespace my;

std::string ServerLink::typeToString(Type type) {
    switch (type) {
        case PLAYER:
            return "player";
        case FOOD:
            return "food";
        case LINEMATE:
            return "linemate";
        case DERAUMERE:
            return "deraumere";
        case SIBUR:
            return "sibur";
        case MENDIANE:
            return "mendiane";
        case PHIRAS:
            return "phiras";
        case THYSTAME:
            return "thystame";
        default:
            return "none";
    }
}

ServerLink::ServerLink(const Args &args): _socket(args.getFlagValue<std::string>("-h"), args.getFlagValue<int>("-p")) {
    if (_socket.read() != "WELCOME\n")
        throw my::MyError("Wrong welcome message", "main");
    _team = args.getFlagValue<std::string>("-n");
    _socket.write(_team + "\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto response = my::split(_socket.read(), " \n");
    if (response[0] == "ko")
        throw my::MyError("main", "Wrong team " + _team);
    _mapSize = std::make_pair(std::stoi(response[1]), std::stoi(response[2]));
    std::cout << "nbr clients remaining: " << response[0] << std::endl;
    std::cout << "map: " << _mapSize.first << " " << _mapSize.second << std::endl;
}

ServerLink::~ServerLink() {}

const std::string &ServerLink::team() const {
    return _team;
}

const std::pair<int, int> &ServerLink::mapSize() const {
    return _mapSize;
}

void ServerLink::forward() {
    _socket.write("Forward\n");
    _read();
}

void ServerLink::left() {
    _socket.write("Left\n");
    _read();
}

void ServerLink::right() {
    _socket.write("Right\n");
    _read();
}

std::vector<std::vector<ServerLink::Type>> ServerLink::look() {
    _socket.write("Look\n");
    auto responses = _read();
    if (responses.size() != 1)
        throw my::MyError("ServerLink::look", "Wrong response");
    std::string response = responses[0].substr(1, responses[0].size() - 2);
    auto map = my::splitWithEmpty(response, ",");
    std::vector<std::vector<ServerLink::Type>> res;
    for (auto &line: map) {
        std::vector<ServerLink::Type> tmp;
        auto resources = my::split(line, " ");
        for (auto &resource: resources) {
            if (resource == "player")
                tmp.push_back(ServerLink::Type::PLAYER);
            else if (resource == "food")
                tmp.push_back(ServerLink::Type::FOOD);
            else if (resource == "linemate")
                tmp.push_back(ServerLink::Type::LINEMATE);
            else if (resource == "deraumere")
                tmp.push_back(ServerLink::Type::DERAUMERE);
            else if (resource == "sibur")
                tmp.push_back(ServerLink::Type::SIBUR);
            else if (resource == "mendiane")
                tmp.push_back(ServerLink::Type::MENDIANE);
            else if (resource == "phiras")
                tmp.push_back(ServerLink::Type::PHIRAS);
            else if (resource == "thystame")
                tmp.push_back(ServerLink::Type::THYSTAME);
            else
                tmp.push_back(ServerLink::Type::NONE);
        }
        res.push_back(tmp);
    }
    return res;
}

std::map<ServerLink::Type, int> ServerLink::inventory() {
    _socket.write("Inventory\n");
    auto responses = _read();
    if (responses.size() != 1)
        throw my::MyError("ServerLink::inventory", "Wrong response");
    std::string response = responses[0].substr(1, responses[0].size() - 2);
    auto map = my::split(response, ",");
    std::map<ServerLink::Type, int> res;
    for (auto &line: map) {
        auto resources = my::split(line, " ");
        if (resources[0] == "player")
            res[ServerLink::Type::PLAYER] = std::stoi(resources[1]);
        else if (resources[0] == "food")
            res[ServerLink::Type::FOOD] = std::stoi(resources[1]);
        else if (resources[0] == "linemate")
            res[ServerLink::Type::LINEMATE] = std::stoi(resources[1]);
        else if (resources[0] == "deraumere")
            res[ServerLink::Type::DERAUMERE] = std::stoi(resources[1]);
        else if (resources[0] == "sibur")
            res[ServerLink::Type::SIBUR] = std::stoi(resources[1]);
        else if (resources[0] == "mendiane")
            res[ServerLink::Type::MENDIANE] = std::stoi(resources[1]);
        else if (resources[0] == "phiras")
            res[ServerLink::Type::PHIRAS] = std::stoi(resources[1]);
        else if (resources[0] == "thystame")
            res[ServerLink::Type::THYSTAME] = std::stoi(resources[1]);
    }
    return res;
}

void ServerLink::broadcast(const std::string &message) {
    _socket.write("Broadcast " + message + "\n");
    _read();
}

int ServerLink::connectNbr() {
    _socket.write("Connect_nbr\n");
    auto responses = _read();
    if (responses.size() != 1)
        throw my::MyError("ServerLink::connectNbr", "Wrong response");
    return std::stoi(responses[0]);
}

void ServerLink::fork() {
    _socket.write("Fork\n");
    _read();
}

bool ServerLink::eject() {
    _socket.write("Eject\n");
    auto responses = _read();
    if (responses.size() != 1)
        throw my::MyError("ServerLink::eject", "Wrong response");
    return responses[0] == "ok";
}

bool ServerLink::take(Type type) {
    _socket.write("Take " + typeToString(type) + "\n");
    auto responses = _read();
    if (responses.size() != 1)
        throw my::MyError("ServerLink::take", "Wrong response");
    return responses[0] == "ok";
}

bool ServerLink::set(Type type) {
    _socket.write("Set " + typeToString(type) + "\n");
    auto responses = _read();
    if (responses.size() != 1)
        throw my::MyError("ServerLink::set", "Wrong response");
    return responses[0] == "ok";
}

int ServerLink::incantation() {
    _socket.write("Incantation\n");
    _read();
    auto responses = _read();
    if (responses.size() != 1)
        throw my::MyError("ServerLink::incantation", "Wrong response");
    std::string res = responses[0];
    if (res == "ko\n")
        return -1;
    return std::stoi(res.substr(15, res.size() - 15 - 1));
}

std::optional<std::string> ServerLink::getBroadcast() {
    if (_broadcast.empty())
        return std::nullopt;
    std::string res = _broadcast;
    _broadcast.clear();
    return res;
}

std::vector<std::string> ServerLink::_read() {
    std::vector<std::string> res;
    while (res.size() == 0) {
        std::string tmp;
        do {
            tmp += _socket.read();
        } while (tmp.back() != '\n');
        tmp = tmp.substr(0, tmp.size() - 1);
        res = my::split(tmp, "\n");
        for (auto it = res.begin(); it != res.end();) {
            if (it->find("message") == 0) {
                _setBroadcast(*it);
                it = res.erase(it);
                continue;
            } else if (it->find("dead") == 0)
                throw std::runtime_error("Dead");
            ++it;
        }
    }
    return res;
}

void ServerLink::_setBroadcast(const std::string &command) {
    _broadcast = command.substr(11, command.size() - 11 - 1);
}
