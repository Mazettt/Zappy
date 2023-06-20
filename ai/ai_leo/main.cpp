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
}