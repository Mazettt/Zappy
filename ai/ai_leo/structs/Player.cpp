/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** Player.cpp
*/

#include "Player.hpp"

ZappyAI::Player::Player(int player_number, ZappyAI::Conn &conn) : _conn(conn)
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
    std::string vision = _conn.receiveFromServer();
    std::vector<std::string> vision_vector;
    std::stringstream ss(vision);
    std::string token;

    while (std::getline(ss, token, ',')) {
        vision_vector.push_back(token);
    }
    std::cout << "Vision: " << vision << std::endl;
    return vision_vector;
}

ZappyAI::Player::~Player() {}
