/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** main.hpp
*/

#pragma once

#include <iostream>
#include <string>
#include "../includes/EncapsulationHeader/RayLib.hpp"

namespace ZappyGui {
    class Core {
        public:
            Core(){};
            ~Core(){};
            int checkArgs(int ac, char **av);
        private:
    };
}
