/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** main.cpp
*/

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "structs/Args.hpp"
#include "structs/MyError.hpp"
#include "structs/Player.hpp"


int main(int ac, char **av)
{
    ZappyAI::Args args(ac, av);

    try {
        args.checkArgs();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    std::cout << "Port: " << args.getPort() << std::endl;
    std::cout << "Team name: " << args.getTeamName() << std::endl;
    std::cout << "Machine: " << args.getMachine() << std::endl;
    ZappyAI::Conn conn(args.getPort(), args.getMachine());

    try {
        conn.connectToServer();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    std::cout << "Connected to server" << std::endl;
    std::cout << "Initiating player" << std::endl;
    std::vector<std::string> infos = conn.initPlayer(args.getTeamName());
    std::cout << "Player initiated" << std::endl;
    int player_number = std::stoi(infos[0]);
    int map_x = std::stoi(infos[1].substr(0, infos[1].find(" ")));
    int map_y = std::stoi(infos[1].substr(infos[1].find(" ") + 1, infos[1].length()));
    ZappyAI::Player player(player_number, conn);
    player.getVision();
}