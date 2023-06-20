/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** Player.hpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Conn.hpp"

namespace ZappyAI {
    class Player {
        public:
            int _player_number;
            int _level;
            int _food;
            int _linemate;
            int _deraumere;
            int _sibur;
            int _mendiane;
            int _phiras;
            int _thystame;
            std::map<std::string, int> _inventory;
            std::vector<std::string> _vision;
            ZappyAI::Conn &_conn;

            Player(int player_number, ZappyAI::Conn &conn);
            ~Player();
            std::vector<std::string> getVision();
    };
}