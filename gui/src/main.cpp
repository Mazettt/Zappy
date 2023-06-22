/*
** EPITECH PROJECT, 2022
** gui
** File description:
** main.c
*/

#include "../includes/Core.hpp"
#include "../includes/Game.hpp"
using namespace ZappyGui;

int main(int ac, char **av) {
    Core core;
    MyRayLib::MyRayLibWindow::MySetTraceLogLevel(LOG_NONE);
    try {
        core.checkArgs(ac, av);
        core.run();
    } catch (const std::exception &e) {
        std::cerr << "aaa " << e.what() << '\n';
        return 84;
    }
    return 0;
}
