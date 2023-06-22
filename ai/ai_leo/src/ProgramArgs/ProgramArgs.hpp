/*
** EPITECH PROJECT, 2022
** ai_leo
** File description:
** ProgramArgs.hpp
*/

#ifndef PROGRAMARGS_HPP_
#define PROGRAMARGS_HPP_

#include <iostream>
#include <string>
#include <vector>

class ProgramArgs {
    public:
        ProgramArgs(int ac, char **av);
        ~ProgramArgs();
        void checkArgs();
        void affUsage();
        int getPort() const;
        std::string getName() const;
        std::string getMachine() const;
    private:
        int _port;
        std::string _name;
        std::string _machine;
};

#endif /* !PROGRAMARGS_HPP_ */