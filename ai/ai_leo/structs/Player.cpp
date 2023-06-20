/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** Player.cpp
*/

#include "Player.hpp"

ZappyAI::Player::Player(int player_number, ZappyAI::Conn conn) : _conn(conn)
{
    _player_number = player_number;
    _level = 1;
    _food = 10;
    _linemate = 0;
    _deraumere = 0;
    _sibur = 0;
    _mendiane = 0;
    _phiras = 0;
    _thystame = 0;
    _inventory["food"] = _food;
    _inventory["linemate"] = _linemate;
    _inventory["deraumere"] = _deraumere;
    _inventory["sibur"] = _sibur;
    _inventory["mendiane"] = _mendiane;
    _inventory["phiras"] = _phiras;
    _inventory["thystame"] = _thystame;
    _conn = conn;
}

std::vector<std::string> ZappyAI::Player::getVision()
{
    _conn.sendToServer("Look\n");
    std::string response = _conn.receiveVision();
    for (int i = 0; i < response.length(); i++) {
        if (response[i] == '[' || response[i] == ']')
            response.erase(i, 1);
    }

    std::vector<std::string> vision;
    std::string tmp = "";
    for (int i = 0; i < response.length(); i++) {
        if (response[i] == ',') {
            vision.push_back(tmp);
            tmp = "";
        } else {
            tmp += response[i];
        }
    }
    vision.push_back(tmp);
    return vision;
}

ZappyAI::Player::~Player() {}

void ZappyAI::Player::play()
{
    _is_dead = false;
    std::cout << "Player " << _player_number << " is playing" << std::endl;
    std::vector<std::string> vision = getVision();

    while (!_is_dead) {
        forward();
    }
    std::cout << "Player " << _player_number << " is dead" << std::endl;
    exit(0);
}

void ZappyAI::Player::forward()
{
    _conn.sendToServer("Forward\n");
    if (_conn.receiveFromServer() == "ok\n")
        std::cout << "Player " << _player_number << " moved forward" << std::endl;
    else {
        std::cout << "Player " << _player_number << " failed to move forward" << std::endl;
        _is_dead = true;
    }
}