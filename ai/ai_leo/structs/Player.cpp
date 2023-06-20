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
    _requirements[0] = "player";
    _requirements[1] = "linemate";
    _requirements[2] = "deraumere";
    _requirements[3] = "sibur";
    _requirements[4] = "mendiane";
    _requirements[5] = "phiras";
    _requirements[6] = "thystame";
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
    _players_on_tile = 0;
    for (int i = 0; i < vision[0].length(); i++) {
        if (vision[0][i] == 'p')
            _players_on_tile++;
    }
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
    while (_inventory["food"] < 15) {
        std::vector<std::string> vision = getVision();
        for (int i = 0; i < vision.size(); i++) {
            if (vision[i].find("food") != std::string::npos) {
                get_pos_from_vision(i);
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
        getInventory();
    }
    std::cout << "Player " << _player_number << " is not starving anymore" << std::endl;
}

bool ZappyAI::Player::check_interest()
{
    std::vector<std::string> vision = getVision();

    for (int i = 0; i < vision.size(); i++) {
        // check each case of vision and check if it contains something needed in _current_requirements
        // strings value are in _requirements
        for (int j = 0; _requirements[j] != ""; j++) {
            if (vision[i].find(_requirements[j]) != std::string::npos && _current_requirements[j] > 0 && _requirements[j] != "player") {
                std::cout << "Player " << _player_number << " found " << _requirements[j] << std::endl;
                get_pos_from_vision(i);
                _conn.sendToServer("Take " + _requirements[j] + "\n");
                if (_conn.receiveFromServer() == "ok\n") {
                    std::cout << "Player " << _player_number << " took " << _requirements[j] << std::endl;
                    _inventory[_requirements[j]]++;
                    _current_requirements[j]--;
                }
                return true;
            }
        }
    }
}

void ZappyAI::Player::vaccuum(std::string const &content)
{
    std::cout << "PLAYER CELL CONTENT : " << content << std::endl;
}

void ZappyAI::Player::wander()
{
    std::vector<std::string> vis = getVision();
    // take everything on the player's case
    for (int i = 0; i < vis[0].length(); i++) {
        if (vis[0][i] != ' ') {
            std::string word = "";
            while (vis[0][i] != ' ' && i < vis[0].length()) {
                word += vis[0][i];
                i++;
            }
            _conn.sendToServer("Take " + word + "\n");
            if (_conn.receiveFromServer() == "ok\n") {
                std::cout << "Player " << _player_number << " took " << word << std::endl;
                _inventory[word]++;
            }
        }
    }
    forward();
    left();
    if (check_interest() == true) {
        return;
    }
    right();
    right();
    if (check_interest() == true) {
        return;
    }
    left();
}

void ZappyAI::Player::drop_required_items()
{
    for (int i = 0; _requirements[i] != ""; i++) {
        if (_requirements[i] == "player")
            continue;
        while (_inventory[_requirements[i]] > 0) {
            _conn.sendToServer("Set " + _requirements[i] + "\n");
            if (_conn.receiveFromServer() == "ok\n") {
                _inventory[_requirements[i]]--;
            }
        }
    }
}

void ZappyAI::Player::levelUp()
{
    if (_level == 1) {
        drop_required_items();
        _conn.sendToServer("Incantation\n");
        std::string resp = _conn.receiveFromServer();
        while (resp != "Current level: 2\n") {
            resp = _conn.receiveFromServer();
            if (resp == "ko\n") {
                std::cout << "Player " << _player_number << " can't level up" << std::endl;
                return;
            }
            if (resp == "Elevation underway\n") {
                std::cout << "Player " << _player_number << " is leveling up" << std::endl;
                _level++;
                set_current_requirements();
                return;
            }
        }
        std::cout << resp << std::endl;
        if (resp == "Current level: 2\n") {
            std::cout << "Player " << _player_number << " leveled up" << std::endl;
            _level++;
            set_current_requirements();
            return;
        }
    } else {
        std::cout << "NEED TO IMPLEMENT LEVEL 2" << std::endl;
    }
    getInventory();
}

void ZappyAI::Player::play()
{
    _is_dead = false;
    std::cout << "Player " << _player_number << " is playing" << std::endl;
    std::vector<std::string> vision = getVision();
    getInventory();

    while (!_is_dead) {
        vision = getVision();
        getInventory();
        set_current_requirements();
        if (_inventory["food"] <= 2)
            emergencyFood();
        if (check_requirements()) {
            std::cout << "Player " << _player_number << " can level up" << std::endl;
            levelUp();
        }
        wander();

    }
    std::cout << "Player " << _player_number << " is dead" << std::endl;
    exit(0);
}

void ZappyAI::Player::set_current_requirements()
{
    // 0 = players, 1 = linemate, 2 = deraumere, 3 = sibur, 4 = mendiane, 5 = phiras, 6 = thystame
    if (_level == 1) {
        _current_requirements[0] = 1;
        _current_requirements[1] = 1;
        _current_requirements[2] = 0;
        _current_requirements[3] = 0;
        _current_requirements[4] = 0;
        _current_requirements[5] = 0;
        _current_requirements[6] = 0;
    } else if (_level == 2) {
        _current_requirements[0] = 2;
        _current_requirements[1] = 1;
        _current_requirements[2] = 1;
        _current_requirements[3] = 1;
        _current_requirements[4] = 0;
        _current_requirements[5] = 0;
        _current_requirements[6] = 0;
    } else if (_level == 3) {
        _current_requirements[0] = 2;
        _current_requirements[1] = 2;
        _current_requirements[2] = 0;
        _current_requirements[3] = 1;
        _current_requirements[4] = 0;
        _current_requirements[5] = 2;
        _current_requirements[6] = 0;
    } else if (_level == 4) {
        _current_requirements[0] = 4;
        _current_requirements[1] = 1;
        _current_requirements[2] = 1;
        _current_requirements[3] = 2;
        _current_requirements[4] = 0;
        _current_requirements[5] = 1;
        _current_requirements[6] = 0;
    } else if (_level == 5) {
        _current_requirements[0] = 4;
        _current_requirements[1] = 1;
        _current_requirements[2] = 2;
        _current_requirements[3] = 1;
        _current_requirements[4] = 3;
        _current_requirements[5] = 0;
        _current_requirements[6] = 0;
    } else if (_level == 6) {
        _current_requirements[0] = 6;
        _current_requirements[1] = 1;
        _current_requirements[2] = 2;
        _current_requirements[3] = 3;
        _current_requirements[4] = 0;
        _current_requirements[5] = 1;
        _current_requirements[6] = 0;
    } else if (_level == 7) {
        _current_requirements[0] = 6;
        _current_requirements[1] = 2;
        _current_requirements[2] = 2;
        _current_requirements[3] = 2;
        _current_requirements[4] = 2;
        _current_requirements[5] = 2;
        _current_requirements[6] = 1;
    }
    for (int i = 0; i < 7; i++) {
        _to_take[i] = _current_requirements[i];
    }
}

bool ZappyAI::Player::check_requirements()
{
    if (_current_requirements[0] > _players_on_tile)
        return false;
    if (_current_requirements[1] > _inventory["linemate"])
        return false;
    if (_current_requirements[2] > _inventory["deraumere"])
        return false;
    if (_current_requirements[3] > _inventory["sibur"])
        return false;
    if (_current_requirements[4] > _inventory["mendiane"])
        return false;
    if (_current_requirements[5] > _inventory["phiras"])
        return false;
    if (_current_requirements[6] > _inventory["thystame"])
        return false;
    return true;
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
    std::cout << "Player " << _player_number << " inventory: " << response << std::endl;
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