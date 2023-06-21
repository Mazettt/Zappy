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
#include <time.h>
#include <future>
#include <chrono>
#include <thread>

namespace ZappyAI {
    class Player {
        public:
            bool _is_dead;
            bool _is_broadcaster = false;
            int _player_number;
            int _level;
            int _food;
            int _linemate;
            int _deraumere;
            int _sibur;
            int _mendiane;
            int _phiras;
            int _thystame;
            int _players_on_tile;
            int _current_requirements[7];
            // variable that has requirements string
            std::string _requirements[7];
            int _to_take[7];
            void vacuum(std::vector<std::string> &vision, std::string const &object);
            bool check_requirements();
            std::map<std::string, int> _inventory;
            std::vector<std::string> _vision;
            ZappyAI::Conn _conn;
            void left();
            void right();
            void forward();
            void take(std::string const &object);
            void refresh_inventory();
            void play();
            void getInventory();
            void emergencyFood();
            void moveTo(int x, int y);
            void set_current_requirements();
            void levelUp();
            void broadcast(std::string const &message);
            Player(int player_number, ZappyAI::Conn conn);
            ~Player();
            std::vector<std::string> getVision();
            void get_pos_from_vision(int i);
            void wander();
            void vaccuum(std::string const &object);
            bool check_interest();
            void drop_required_items();
    };
}