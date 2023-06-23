/*
** EPITECH PROJECT, 2022
** ai_leo
** File description:
** Player.hpp
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include "../Socket/Socket.hpp"

class Player {
    public:
        int playerNumber;
        int level;
        int mapSizeX;
        int mapSizeY;
        bool emergency;
        void go_to(int destination);
        std::vector<std::string> View;
        std::map<std::string, int> Inventory;
        std::queue<std::string> broadcasts;
        std::vector<std::string> split(const std::string &str, const std::string &delimiter);
        void vacuum();
        void harvest_interesting_stuff();
        bool do_broadcast_has(std::string message);
        void play();
        Socket socket;
        bool check_lvl_up();
        std::map<std::string, int> get_requirements();
        void crave_food();
        int most_x(std::string object);
        std::string forward();
        std::string right();
        std::string left();
        std::string broadcast(std::string message);
        void go_to_sound(std::string sound_direction);
        std::string set_object(std::string object);
        std::vector<std::string> look();
        std::string take(std::string object);
        std::map<std::string, int> inventory();
        // faire une fct read qui doit read le socket
        // si le message commence par "message", je continue de read
        std::string read();
        std::string read_try();
        void try_level_up();
        void display_inventory();
        ~Player() {};
        Player() {};
    private:
};

#endif /* !PLAYER_HPP_ */