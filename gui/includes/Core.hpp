/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** main.hpp
*/

#pragma once

#include <iostream>
#include <string>
#include "../Utils/MyError.hpp"
// RAYLIB HEADERS
#include "../includes/MyRayLibHeader/Window.hpp"
#include "../includes/MyRayLibHeader/Draw.hpp"

// NETWORKING HEADERS
#include "../includes/MySocketHeader/Network.hpp"

namespace ZappyGui {
   class Core {
        public:
            Core();
            ~Core(){};
            int checkArgs(int ac, char **av);
            int handleConnectionServer(int ac, char **av);
        protected:
            int _port;
            std::string _ip;
        private:
    };
}
