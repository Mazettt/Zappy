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