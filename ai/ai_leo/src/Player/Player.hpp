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
#include "../Socket/Socket.hpp"

class Player {
    public:
        int playerNumber;
        int level;
        int mapSizeX;
        int mapSizeY;
        std::vector<std::string> View;
        std::map<std::string, int> Inventory;
        void vacuum();
        void play();
        Socket socket;
        std::map<std::string, int> get_requirements();

        std::string forward();
        std::string right();
        std::string left();
        std::vector<std::string> look();
        std::string take(std::string object);
        std::map<std::string, int> inventory();
        void display_inventory();
        ~Player() {};
        Player() {};
    private:
};

#endif /* !PLAYER_HPP_ */