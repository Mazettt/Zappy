/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** Args.hpp
*/

#ifndef ARGS_HPP_
#define ARGS_HPP_

#include <string>
#include <vector>

namespace ZappyAI {
    class Args {
        public:
            int _port;
            std::string _teamName;
            std::string _machine;
            std::vector<std::string> _args;
            Args(int ac, char **av);
            ~Args() = default;
            void checkArgs();
            int getPort() const;
            std::string getTeamName() const;
            std::string getMachine() const;
            std::vector<std::string> getArgs() const;
            void check_empty();
    };
};

#endif /* !ARGS_HPP_ */