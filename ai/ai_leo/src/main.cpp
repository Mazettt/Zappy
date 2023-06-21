/*
** EPITECH PROJECT, 2022
** ai_leo
** File description:
** main.cpp
*/

#include "Socket/Socket.hpp"
#include "ProgramArgs/ProgramArgs.hpp"

void aff_usage()
{
    std::cout << "USAGE:\t./zappy_ai -p port -n name -h machine" << std::endl;
    std::cout << "\tport\tis the port number" << std::endl;
    std::cout << "\tname\tis the name of the team" << std::endl;
    std::cout << "\tmachine\tis the name of the machine; localhost by default" << std::endl;
}



int main(int ac, char **av)
{
    ProgramArgs args(ac, av);
    std::cout << "port: " << args.getPort() << std::endl;
    std::cout << "name: " << args.getName() << std::endl;
    std::cout << "machine: " << args.getMachine() << std::endl;

    return (0);
}