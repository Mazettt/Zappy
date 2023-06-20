/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** Args.cpp
*/

#include "Args.hpp"
#include "MyError.hpp"

ZappyAI::Args::Args(int ac, char **av)
{
    for (int i = 0; i < ac; i++)
        _args.push_back(av[i]);
}

void ZappyAI::Args::check_empty()
{
    if (_port == 0)
        throw MyError("Error: -p must be followed by a port number");
    if (_teamName == "")
        throw MyError("Error: -n must be followed by a team name");
    if (_machine == "")
        _machine = "localhost";
}

void ZappyAI::Args::checkArgs()
{
    for (int i = 1; i < _args.size(); i++) {
        if (_args[i] == "-p") {
            if (i + 1 >= _args.size())
                throw MyError("Error: -p must be followed by a port number");
            _port = std::stoi(_args[i + 1]);
            i++;
        } else if (_args[i] == "-n") {
            if (i + 1 >= _args.size())
                throw MyError("Error: -n must be followed by a team name");
            _teamName = _args[i + 1];
            i++;
        } else if (_args[i] == "-h") {
            if (i + 1 >= _args.size())
                _machine = "localhost";
            _machine = _args[i + 1];
            i++;
        } else
            throw MyError("Error: invalid argument");
    }
    check_empty();
}

std::string ZappyAI::Args::getTeamName() const
{
    return _teamName;
}

std::string ZappyAI::Args::getMachine() const
{
    return _machine;
}

int ZappyAI::Args::getPort() const
{
    return _port;
}

std::vector<std::string> ZappyAI::Args::getArgs() const
{
    return _args;
}