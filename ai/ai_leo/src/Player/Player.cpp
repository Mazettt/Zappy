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
        std::cout << "Player " << playerNumber << " is playing" << std::endl;
        View = look();
        Inventory = inventory();
        display_inventory();
        vacuum();
        exit(0);
    }
}

void Player::display_inventory()
{
    std::cout << "Player " << playerNumber << " inventory:" << std::endl;
    for (auto it = Inventory.begin(); it != Inventory.end(); it++) {
        std::cout << it->first << ": " << it->second << std::endl;
    }
}

void Player::vacuum()
{
    std::string player_tile = View[0];
    std::string object;
    std::string tmp;

    while (player_tile[0] == ' ')
        player_tile.erase(0, 1);
    for (int i = 0; i < player_tile.size() + 1; i++) {
        if (player_tile[i] == ' ' || player_tile[i] == '\0') {
            object = tmp;
            if (object != "player" && object != " ") {
                if (take(object) == "ok")
                    std::cout << "Player " << playerNumber << " took " << object << std::endl;
                else
                    std::cout << "Player " << playerNumber << " failed to take " << object << std::endl;
            }
            tmp.clear();
        } else {
            tmp += player_tile[i];
        }
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

std::string Player::take(std::string object)
{
    socket.sendSocket("Take " + object + "\n");
    if (socket.receiveSocket() == "ok\n") {
        Inventory[object]++;
        return ("ok");
    }
    return ("ko");
}