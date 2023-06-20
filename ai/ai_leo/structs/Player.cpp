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

void ZappyAI::Player::moveTo(int x, int y)
{
    if (x > 0) {
        for (int i = 0; i < x; i++) {
            _conn.sendToServer("Forward\n");
            _conn.receiveFromServer();
        }
    } else if (x < 0) {
        for (int i = 0; i < -x; i++) {
            _conn.sendToServer("Forward\n");
            _conn.receiveFromServer();
        }
    }

    if (y > 0) {
        _conn.sendToServer("Left\n");
        _conn.receiveFromServer();
        for (int i = 0; i < y; i++) {
            _conn.sendToServer("Forward\n");
            _conn.receiveFromServer();
        }
    } else if (y < 0) {
        _conn.sendToServer("Right\n");
        _conn.receiveFromServer();
        for (int i = 0; i < -y; i++) {
            _conn.sendToServer("Forward\n");
            _conn.receiveFromServer();
        }
    }
}

void ZappyAI::Player::get_pos_from_vision(int i)
{
    int x = 0;
    int y = 0;

    if (i == 0) {
        x = 0;
        y = 0;
    } else if (i == 1) {
        x = 1;
        y = -1;
    } else if (i == 2) {
        x = 1;
        y = 0;
    } else if (i == 3) {
        x = 1;
        y = 1;
    } else if (i == 4) {
        x = 2;
        y = -2;
    } else if (i == 5) {
        x = 2;
        y = -1;
    } else if (i == 6) {
        x = 2;
        y = 0;
    } else if (i == 7) {
        x = 2;
        y = 1;
    } else if (i == 8) {
        x = 2;
        y = 2;
    } else if (i == 9) {
        x = 3;
        y = -3;
    } else if (i == 10) {
        x = 3;
        y = -2;
    } else if (i == 11) {
        x = 3;
        y = -1;
    } else if (i == 12) {
        x = 3;
        y = 0;
    } else if (i == 13) {
        x = 3;
        y = 1;
    } else if (i == 14) {
        x = 3;
        y = 2;
    } else if (i == 15) {
        x = 3;
        y = 3;
    } else if (i == 16) {
        x = 4;
        y = -4;
    } else if (i == 17) {
        x = 4;
        y = -3;
    } else if (i == 18) {
        x = 4;
        y = -2;
    } else if (i == 19) {
        x = 4;
        y = -1;
    } else if (i == 20) {
        x = 4;
        y = 0;
    } else if (i == 21) {
        x = 4;
        y = 1;
    } else if (i == 22) {
        x = 4;
        y = 2;
    } else if (i == 23) {
        x = 4;
        y = 3;
    } else if (i == 24) {
        x = 4;
        y = 4;
    }
    moveTo(x, y);
}

void ZappyAI::Player::emergencyFood()
{
    std::cout << "Player " << _player_number << " is starving" << std::endl;
    while (_inventory["food"] < 10) {
        std::vector<std::string> vision = getVision();
        for (int i = 0; i < vision.size(); i++) {
            if (vision[i].find("food") != std::string::npos) {
                get_pos_from_vision(i);
                // count the number of food
                int food = 0;
                for (int j = 0; j < vision[i].length(); j++) {
                    if (vision[i][j] == 'f')
                        food++;
                }
                for (int j = 0; j < food; j++) {
                    _conn.sendToServer("Take food\n");
                    if (_conn.receiveFromServer() == "ok\n") {
                        _inventory["food"]++;
                    }
                }
            }
        }
        forward();
    }
    std::cout << "Player " << _player_number << " is not starving anymore" << std::endl;
}

void ZappyAI::Player::play()
{
    _is_dead = false;
    std::cout << "Player " << _player_number << " is playing" << std::endl;
    std::vector<std::string> vision = getVision();
    getInventory();

    while (!_is_dead) {
        
        getInventory();
        if (_inventory["food"] <= 2)
            emergencyFood();
    }
    std::cout << "Player " << _player_number << " is dead" << std::endl;
    exit(0);
}

void ZappyAI::Player::forward()
{
    _conn.sendToServer("Forward\n");
    if (_conn.receiveFromServer() == "ok\n")
        return;
    else {
        std::cout << "Player " << _player_number << " failed to move forward" << std::endl;
        _is_dead = true;
    }
}

void ZappyAI::Player::left()
{
    _conn.sendToServer("Left\n");
    if (_conn.receiveFromServer() == "ok\n")
        return;
    else {
        std::cout << "Player " << _player_number << " failed to turn left" << std::endl;
        _is_dead = true;
    }
}

void ZappyAI::Player::right()
{
    _conn.sendToServer("Right\n");
    if (_conn.receiveFromServer() == "ok\n")
        return;
    else {
        std::cout << "Player " << _player_number << " failed to turn right" << std::endl;
        _is_dead = true;
    }
}

void ZappyAI::Player::refresh_inventory()
{
    _inventory["food"] = _food;
    _inventory["linemate"] = _linemate;
    _inventory["deraumere"] = _deraumere;
    _inventory["sibur"] = _sibur;
    _inventory["mendiane"] = _mendiane;
    _inventory["phiras"] = _phiras;
    _inventory["thystame"] = _thystame;
}

void ZappyAI::Player::getInventory()
{
    _conn.sendToServer("Inventory\n");
    std::string response = _conn.receiveInventory();
    for (int i = 0; i < response.length(); i++) {
        if (response[i] == '[' || response[i] == ']')
            response.erase(i, 1);
    }
    std::vector<std::string> inventory;
    std::string tmp = "";
    for (int i = 0; i < response.length(); i++) {
        if (response[i] == ',') {
            inventory.push_back(tmp);
            tmp = "";
        } else {
            tmp += response[i];
        }
    }
    inventory.push_back(tmp);
    for (int i = 0; i < inventory.size(); i++) {
        if (inventory[i][0] == ' ')
            inventory[i].erase(0, 1);
    }
    for (int i = 0; i < inventory.size(); i++) {
        std::string object = inventory[i].substr(0, inventory[i].find(' '));
        int quantity = std::stoi(inventory[i].substr(inventory[i].find(' ') + 1, inventory[i].length()));
        if (object == "food")
            _food = quantity;
        else if (object == "linemate")
            _linemate = quantity;
        else if (object == "deraumere")
            _deraumere = quantity;
        else if (object == "sibur")
            _sibur = quantity;
        else if (object == "mendiane")
            _mendiane = quantity;
        else if (object == "phiras")
            _phiras = quantity;
        else if (object == "thystame")
            _thystame = quantity;
    }
    refresh_inventory();
}

void ZappyAI::Player::take(std::string const &object)
{
    _conn.sendToServer("Take " + object + "\n");
    if (_conn.receiveFromServer() == "ok\n") {
        std::cout << "Player " << _player_number << " took " << object << std::endl;
        if (object == "food")
            _food++;
        else if (object == "linemate")
            _linemate++;
        else if (object == "deraumere")
            _deraumere++;
        else if (object == "sibur")
            _sibur++;
        else if (object == "mendiane")
            _mendiane++;
        else if (object == "phiras")
            _phiras++;
        else if (object == "thystame")
            _thystame++;
        refresh_inventory();
    }
    else {
        std::cout << "Player " << _player_number << " failed to take " << object << std::endl;
        _is_dead = true;
    }
}