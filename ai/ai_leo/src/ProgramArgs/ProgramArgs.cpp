/*
** EPITECH PROJECT, 2022
** ai_leo
** File description:
** ProgramArgs.cpp
*/

#include "ProgramArgs.hpp"

ProgramArgs::ProgramArgs(int ac, char **av)
{
    for (int i = 1; i < ac; i++) {
        if (std::string(av[i]) == "-p") {
            if (av[i + 1] == NULL) {
                affUsage();
                exit(84);
            }
            _port = std::stoi(av[i + 1]);
            i++;
        } else if (std::string(av[i]) == "-n") {
            if (av[i + 1] == NULL) {
                affUsage();
                exit(84);
            }
            _name = av[i + 1];
            i++;
        } else if (std::string(av[i]) == "-h") {
            if (av[i + 1] == NULL) {
                _machine = "localhost";
                break;
            } else {
                _machine = av[i + 1];
                break;
            }
            i++;
        }
    }

    if (_port == 0 || _name == "") {
        affUsage();
        exit(84);
    }
    if (_machine == "")
        _machine = "localhost";
}

ProgramArgs::~ProgramArgs()
{
}

void ProgramArgs::affUsage()
{
    std::cout << "USAGE:\t./zappy_ai -p port -n name -h machine" << std::endl;
    std::cout << "\tport\tis the port number" << std::endl;
    std::cout << "\tname\tis the name of the team" << std::endl;
    std::cout << "\tmachine\tis the name of the machine; localhost by default" << std::endl;
}

int ProgramArgs::getPort() const
{
    return (_port);
}

std::string ProgramArgs::getName() const
{
    return (_name);
}

std::string ProgramArgs::getMachine() const
{
    return (_machine);
}