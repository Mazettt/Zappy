/*
** EPITECH PROJECT, 2022
** ai_leo
** File description:
** Player.cpp
*/

#include "Player.hpp"

void Player::play()
{
    while (true) {
        Inventory = inventory();
        exit(0);
    }
}

std::string Player::forward()
{
    socket.sendSocket("Forward\n");
    if (socket.receiveSocket() == "ok\n")
        return ("ok");
    return ("ko");
}

std::string Player::right()
{
    socket.sendSocket("Right\n");
    if (socket.receiveSocket() == "ok\n")
        return ("ok");
    return ("ko");
}

std::string Player::left()
{
    socket.sendSocket("Left\n");
    if (socket.receiveSocket() == "ok\n")
        return ("ok");
    return ("ko");
}

std::vector<std::string> Player::look()
{
    socket.sendSocket("Look\n");
    std::string msg;
    while (msg.find(']') == std::string::npos) {
        msg += socket.receiveSocket();
    }
    std::vector<std::string> view;
    std::string tmp;
    msg.erase(0, 1);
    for (int i = 0; i < msg.size() + 1; i++) {
        if (msg[i] == ',' || msg[i] == ']') {
            view.push_back(tmp);
            tmp.clear();
        } else {
            tmp += msg[i];
        }
    }
    return (view);
}

std::map<std::string, int> Player::inventory()
{
    socket.sendSocket("Inventory\n");
    std::string msg;
    while (msg.find(']') == std::string::npos) {
        msg += socket.receiveSocket();
    }
    std::cout << msg << std::endl;
    std::map<std::string, int> Inventory;
    std::string tmp;
    msg.erase(0, 1);
    for (int i = 0; i < msg.size() + 1; i++) {
        if (msg[i] == ',' || msg[i] == ']') {
            if (tmp[0] == ' ')
                tmp.erase(0, 1);
            Inventory[tmp.substr(0, tmp.find(' '))] = std::stoi(tmp.substr(tmp.find(' ') + 1, tmp.size()));
            tmp.clear();
        } else {
            tmp += msg[i];
        }
    }
    return (Inventory);
}

std::map<std::string, int> Player::get_requirements()
{
    std::map<std::string, int> requirements;
    if (level == 1) {
        requirements["linemate"] = 1;
        requirements["deraumere"] = 0;
        requirements["sibur"] = 0;
        requirements["mendiane"] = 0;
        requirements["phiras"] = 0;
        requirements["thystame"] = 0;
    } else if (level == 2) {
        requirements["linemate"] = 1;
        requirements["deraumere"] = 1;
        requirements["sibur"] = 1;
        requirements["mendiane"] = 0;
        requirements["phiras"] = 0;
        requirements["thystame"] = 0;
    } else if (level == 3) {
        requirements["linemate"] = 2;
        requirements["deraumere"] = 0;
        requirements["sibur"] = 1;
        requirements["mendiane"] = 0;
        requirements["phiras"] = 2;
        requirements["thystame"] = 0;
    } else if (level == 4) {
        requirements["linemate"] = 1;
        requirements["deraumere"] = 1;
        requirements["sibur"] = 2;
        requirements["mendiane"] = 0;
        requirements["phiras"] = 1;
        requirements["thystame"] = 0;
    } else if (level == 5) {
        requirements["linemate"] = 1;
        requirements["deraumere"] = 2;
        requirements["sibur"] = 1;
        requirements["mendiane"] = 3;
        requirements["phiras"] = 0;
        requirements["thystame"] = 0;
    } else if (level == 6) {
        requirements["linemate"] = 1;
        requirements["deraumere"] = 2;
        requirements["sibur"] = 3;
        requirements["mendiane"] = 0;
        requirements["phiras"] = 1;
        requirements["thystame"] = 0;
    } else if (level == 7) {
        requirements["linemate"] = 2;
        requirements["deraumere"] = 2;
        requirements["sibur"] = 2;
        requirements["mendiane"] = 2;
        requirements["phiras"] = 2;
        requirements["thystame"] = 1;
    }
    return (requirements);
}