/*
** EPITECH PROJECT, 2022
** ai_leo
** File description:
** Player.cpp
*/

#include "Player.hpp"

std::vector<std::string> Player::split(const std::string &str, const std::string &delimiter) {
    std::vector<std::string> result;
    std::string tmp;

    for (const char &c : str) {
        if (delimiter.find(c) != std::string::npos) {
            if (tmp != "")
                result.push_back(tmp);
            tmp.clear();
        } else
            tmp += c;
    }
    if (tmp != "")
        result.push_back(tmp);
    return result;
}

std::string Player::read()
{
    std::string message = socket.receiveSocket();
    std::vector<std::string> split_message = split(message, "\n");


    while (true) {
        for (std::string line : split_message) {
            std::cout << line << std::endl;
            if (line.find("message") == 0) {
                std::string last_char = line.substr(line.size() - 1);
                int last_digit = std::stoi(last_char);
                if (last_digit == level)
                    broadcasts.push(line);
                return (read());
            } else {
                return (line);
            }
        }
    }
}

std::string Player::read_try()
{
    std::string message = socket.receiveSocket_try();
    std::vector<std::string> split_message = split(message, "\n");

    while (true) {
        for (std::string line : split_message) {
            if (line.find("message") == 0) {
                broadcasts.push(line);
            } else {
                return (line);
            }
        }
    }
}

std::string Player::broadcast(std::string message)
{
    std::string command = "Broadcast " + message + "\n";
    socket.sendSocket(command);
    return (read());
}

void Player::go_to(int destination)
{
    int x = 0;
    int y = 0;

    if (destination == 0) {
        return;
    } else if (destination == 1) {
        x = 1;
        y = -1;
    } else if (destination == 2) {
        x = 1;
        y = 0;
    } else if (destination == 3) {
        x = 1;
        y = 1;
    } else if (destination == 4) {
        x = 2;
        y = -2;
    } else if (destination == 5) {
        x = 2;
        y = -1;
    } else if (destination == 6) {
        x = 2;
        y = 0;
    } else if (destination == 7) {
        x = 2;
        y = 1;
    } else if (destination == 8) {
        x = 2;
        y = 2;
    } else if (destination == 9) {
        x = 3;
        y = -3;
    } else if (destination == 10) {
        x = 3;
        y = -2;
    } else if (destination == 11) {
        x = 3;
        y = -1;
    } else if (destination == 12) {
        x = 3;
        y = 0;
    } else if (destination == 13) {
        x = 3;
        y = 1;
    } else if (destination == 14) {
        x = 3;
        y = 2;
    } else if (destination == 15) {
        x = 3;
        y = 3;
    } else if (destination == 16) {
        x = 4;
        y = -4;
    } else if (destination == 17) {
        x = 4;
        y = -3;
    } else if (destination == 18) {
        x = 4;
        y = -2;
    } else if (destination == 19) {
        x = 4;
        y = -1;
    } else if (destination == 20) {
        x = 4;
        y = 0;
    } else if (destination == 21) {
        x = 4;
        y = 1;
    } else if (destination == 22) {
        x = 4;
        y = 2;
    } else if (destination == 23) {
        x = 4;
        y = 3;
    } else if (destination == 24) {
        x = 4;
        y = 4;
    }
    if (x > 0) {
        for (int i = 0; i < x; i++) {
            forward();
        }
    }
    if (y > 0) {
        right();
        for (int i = 0; i < y; i++) {
            forward();
        }
    } else if (y < 0) {
        left();
        for (int i = 0; i < y; i++) {
            forward();
        }
    }
}

int Player::most_x(std::string object)
{
    int counter = 0;
    int tab_counter[View.size()];
    int destination = 0;
    int tmp = 0;

    for (int i = 0; i < View.size(); i++) {
        while (View[i].find(object) != std::string::npos) {
            counter++;
            View[i].erase(View[i].find(object), object.size());
        }
        tab_counter[i] = counter;
    }
    for (int i = 0; i < View.size(); i++) {
        if (tab_counter[i] > tmp) {
            tmp = tab_counter[i];
            destination = i;
        }
    }
    return (destination);
}

void Player::crave_food()
{
    while (Inventory["food"] < 15) {
        View = look();
        int destination = most_x("food");
        if (destination == 0) {
            forward();
            int rand = std::rand() % 2;
            if (rand == 0) {
                left();
            } else {
                right();
            }
        } else {
            go_to(destination);
            View = look();
            vacuum();
            Inventory = inventory();
        }
    }
    emergency = false;
}

void Player::go_to_sound(std::string sound_direction)
{
    if (sound_direction[0] < '0' || sound_direction[0] > '9') {
        return;
    }
    int direction = std::stoi(sound_direction);

    for (int i = 0; i < broadcasts.size(); i++) {
        broadcasts.pop();
    }

    if (direction == 1) {
        forward();
    } else if (direction == 2) {
        forward();
        left();
        forward();
    } else if (direction == 3) {
        left();
        forward();
    } else if (direction == 4) {
        left();
        forward();
        left();
        forward();
    } else if (direction == 5) {
        left();
        left();
        forward();
    } else if (direction == 6) {
        right();
        forward();
        right();
        forward();
    } else if (direction == 7) {
        right();
        forward();
    } else if (direction == 8) {
        forward();
        right();
        forward();
    } else if (direction == 0) {
        return;
    }
}

void Player::try_level_up()
{
    if (level == 1) {
        std::cout << "[Player " << playerNumber << "] Trying to level up 1" << std::endl;
        Inventory = inventory();
        std::map<std::string, int> reqs = get_requirements();
        for (auto it = reqs.begin(); it != reqs.end(); it++) {
            if (it->second < 0) {
                continue;
            }
            for (int i = 0; i < it->second; i++) {
                set_object(it->first);
            }
        }
        socket.sendSocket("Incantation\n");
        std::string response = read();
        response = read();
        if (response.find("ko") != std::string::npos) {
            return;
        } else {
            level++;
            std::cout << response << std::endl;
            std::cout << "[Player " << playerNumber << "] LEVEL UP 2" << std::endl;
            return;
        }
    } else if (level == 2) {
        if (broadcasts.size() == 0) {
            broadcast("I'm level 2");
            View = look();
            int p_count = 0;

            for (int i = 0; View[0][i] != '\0'; i++) {
                if (View[0][i] == 'p' && View[0][i + 1] == 'l') {
                    p_count++;
                }
            }
            if (p_count >= 2) {
                std::cout << "[Player " << playerNumber << "] Trying to level up 2" << std::endl;
                std::map<std::string, int> reqs = get_requirements();
                for (auto it = reqs.begin(); it != reqs.end(); it++) {
                    if (it->second < 0) {
                        continue;
                    }
                    for (int i = 0; i < it->second; i++) {
                        set_object(it->first);
                    }
                }
                socket.sendSocket("Incantation\n");
                std::string response = read();
                response = read();
                if (response.find("ko") != std::string::npos) {
                    return;
                } else {
                    level++;
                    std::cout << response << std::endl;
                    std::cout << "[Player " << playerNumber << "] LEVEL UP 2" << std::endl;
                    return;
                }
            }
        } else {
            std::string sound_direction = broadcasts.front();
            std::string message_x = sound_direction.substr(0, sound_direction.find(","));
            std::string x = message_x.substr(message_x.find(" ") + 1, message_x.size());
            go_to_sound(x);
        }
    } else if (level == 3) {
        if (broadcasts.size() == 0) {
            broadcast("I'm level 3");
            View = look();
            int p_count = 0;

            for (int i = 0; View[0][i] != '\0'; i++) {
                if (View[0][i] == 'p' && View[0][i + 1] == 'l') {
                    p_count++;
                }
            }
            if (p_count >= 2) {
                std::cout << "[Player " << playerNumber << "] Trying to level up 3" << std::endl;
                std::map<std::string, int> reqs = get_requirements();
                for (auto it = reqs.begin(); it != reqs.end(); it++) {
                    if (it->second < 0) {
                        continue;
                    }
                    for (int i = 0; i < it->second; i++) {
                        set_object(it->first);
                    }
                }
                socket.sendSocket("Incantation\n");
                std::string response = read();
                response = read();
                if (response.find("ko") != std::string::npos) {
                    return;
                } else {
                    level++;
                    std::cout << response << std::endl;
                    std::cout << "[Player " << playerNumber << "] LEVEL UP 3" << std::endl;
                    return;
                }
            }
        } else {
            std::string sound_direction = broadcasts.front();
            std::string message_x = sound_direction.substr(0, sound_direction.find(","));
            std::string x = message_x.substr(message_x.find(" ") + 1, message_x.size());
            go_to_sound(x);
        }
    } else if (level == 4) {
        if (broadcasts.size() == 0) {
            broadcast("I'm level 4");
            View = look();
            int p_count = 0;

            for (int i = 0; View[0][i] != '\0'; i++) {
                if (View[0][i] == 'p' && View[0][i + 1] == 'l') {
                    p_count++;
                }
            }
            if (p_count >= 4) {
                std::cout << "[Player " << playerNumber << "] Trying to level up 4" << std::endl;
                std::map<std::string, int> reqs = get_requirements();
                for (auto it = reqs.begin(); it != reqs.end(); it++) {
                    if (it->second < 0) {
                        continue;
                    }
                    for (int i = 0; i < it->second; i++) {
                        set_object(it->first);
                    }
                }
                socket.sendSocket("Incantation\n");
                std::string response = read();
                response = read();
                if (response.find("ko") != std::string::npos) {
                    return;
                } else {
                    level++;
                    std::cout << response << std::endl;
                    std::cout << "[Player " << playerNumber << "] LEVEL UP 4" << std::endl;
                    return;
                }
            }
        } else {
            std::string sound_direction = broadcasts.front();
            std::string message_x = sound_direction.substr(0, sound_direction.find(","));
            std::string x = message_x.substr(message_x.find(" ") + 1, message_x.size());
            go_to_sound(x);
        }
    } else if (level == 5) {
        if (broadcasts.size() == 0) {
            broadcast("I'm level 5");
            View = look();
            int p_count = 0;

            for (int i = 0; View[0][i] != '\0'; i++) {
                if (View[0][i] == 'p' && View[0][i + 1] == 'l') {
                    p_count++;
                }
            }
            if (p_count >= 4) {
                std::cout << "[Player " << playerNumber << "] Trying to level up 5" << std::endl;
                std::map<std::string, int> reqs = get_requirements();
                for (auto it = reqs.begin(); it != reqs.end(); it++) {
                    if (it->second < 0) {
                        continue;
                    }
                    for (int i = 0; i < it->second; i++) {
                        set_object(it->first);
                    }
                }
                socket.sendSocket("Incantation\n");
                std::string response = read();
                response = read();
                if (response.find("ko") != std::string::npos) {
                    return;
                } else {
                    level++;
                    std::cout << response << std::endl;
                    std::cout << "[Player " << playerNumber << "] LEVEL UP 5" << std::endl;
                    return;
                }
            }
        } else {
            std::string sound_direction = broadcasts.front();
            std::string message_x = sound_direction.substr(0, sound_direction.find(","));
            std::string x = message_x.substr(message_x.find(" ") + 1, message_x.size());
            go_to_sound(x);
        }
    } else if (level == 6) {
        if (broadcasts.size() == 0) {
            broadcast("I'm level 6");
            View = look();
            int p_count = 0;

            for (int i = 0; View[0][i] != '\0'; i++) {
                if (View[0][i] == 'p' && View[0][i + 1] == 'l') {
                    p_count++;
                }
            }
            if (p_count >= 6) {
                std::cout << "[Player " << playerNumber << "] Trying to level up 6" << std::endl;
                std::map<std::string, int> reqs = get_requirements();
                for (auto it = reqs.begin(); it != reqs.end(); it++) {
                    if (it->second < 0) {
                        continue;
                    }
                    for (int i = 0; i < it->second; i++) {
                        set_object(it->first);
                    }
                }
                socket.sendSocket("Incantation\n");
                std::string response = read();
                response = read();
                if (response.find("ko") != std::string::npos) {
                    return;
                } else {
                    level++;
                    std::cout << response << std::endl;
                    std::cout << "[Player " << playerNumber << "] LEVEL UP 6" << std::endl;
                    return;
                }
            }
        } else {
            std::string sound_direction = broadcasts.front();
            std::string message_x = sound_direction.substr(0, sound_direction.find(","));
            std::string x = message_x.substr(message_x.find(" ") + 1, message_x.size());
            go_to_sound(x);
        }
    } else if (level == 7) {
        if (broadcasts.size() == 0) {
            broadcast("I'm level 7");
            View = look();
            int p_count = 0;

            for (int i = 0; View[0][i] != '\0'; i++) {
                if (View[0][i] == 'p' && View[0][i + 1] == 'l') {
                    p_count++;
                }
            }
            if (p_count >= 6) {
                std::cout << "[Player " << playerNumber << "] Trying to level up 7" << std::endl;
                std::map<std::string, int> reqs = get_requirements();
                for (auto it = reqs.begin(); it != reqs.end(); it++) {
                    if (it->second < 0) {
                        continue;
                    }
                    for (int i = 0; i < it->second; i++) {
                        set_object(it->first);
                    }
                }
                socket.sendSocket("Incantation\n");
                std::string response = read();
                response = read();
                if (response.find("ko") != std::string::npos) {
                    return;
                } else {
                    level++;
                    std::cout << response << std::endl;
                    std::cout << "[Player " << playerNumber << "] LEVEL UP 7" << std::endl;
                    return;
                }
            }
        } else {
            std::string sound_direction = broadcasts.front();
            std::string message_x = sound_direction.substr(0, sound_direction.find(","));
            std::string x = message_x.substr(message_x.find(" ") + 1, message_x.size());
            go_to_sound(x);
        }
    } else if (level == 8) {
        return;
    }
}

std::string Player::set_object(std::string object)
{
    socket.sendSocket("Set " + object + "\n");
    std::string response = read();
    return (response);
}

void Player::harvest_interesting_stuff()
{
    std::cout << "[Player " << playerNumber << "]: Harvesting interesting stuff" << std::endl;
    View = look();
    int dest = most_x("food");
    go_to(dest);
    vacuum();
}

void Player::play()
{
    level = 1;
    View = look();
    Inventory = inventory();
    vacuum();
    while (true) {
        Inventory = inventory();
        if (Inventory["food"] < 8) {
            std::cout << "ALERTE" << std::endl;
            emergency = true;
        }
    
        if (emergency == true) {
            std::cout << "[Player " << playerNumber << "]: I'm hungry" << std::endl;
            crave_food();
        }
        if (check_lvl_up() == true) {
            try_level_up();
        }
    }
}

bool Player::check_lvl_up()
{
    std::map<std::string, int> reqs = get_requirements();
    std::map<std::string, int> inv_cpy = Inventory;

    for (auto it = reqs.begin(); it != reqs.end(); it++) {
        if (it->first == "food")
            continue;
        if (inv_cpy[it->first] < it->second)
            return (false);
        inv_cpy[it->first] -= it->second;
    }
    return (true);
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
    View = look();
    std::string player_tile = View[0];
    std::string object;
    std::string tmp;
    while (player_tile[0] == ' ')
        player_tile.erase(0, 1);
    for (int i = 0; i < player_tile.size() + 1; i++) {
        if (player_tile[i] == ' ' || player_tile[i] == '\0') {
            object = tmp;
            if (object != "player" && object != " ") {
                take(object);
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
    if (read() == "ok")
        return ("ok");
    return ("ko");
}

std::string Player::right()
{
    socket.sendSocket("Right\n");
    if (read() == "ok")
        return ("ok");
    return ("ko");
}

std::string Player::left()
{
    socket.sendSocket("Left\n");
    if (read() == "ok")
        return ("ok");
    return ("ko");
}

std::vector<std::string> Player::look()
{
    socket.sendSocket("Look\n");
    std::string msg;
    while (msg.find(']') == std::string::npos) {
        msg += read();
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
        msg += read();
    }
    if (msg[0] != '[' && msg[msg.size() - 1] != ']')
        return (Inventory);
    Inventory.clear();
    std::string tmp;
    msg.erase(0, 1);
    for (int i = 0; i < msg.size() + 1; i++) {
        if (msg[i] == ',' || msg[i] == ']') {
            if (tmp[0] == ' ')
                tmp.erase(0, 1);
            if (tmp[0] == '[')
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
    if (read() == "ok\n") {
        Inventory[object]++;
        return ("ok");
    }
    return ("ko");
}