/*
** EPITECH PROJECT, 2022
** gui
** File description:
** main.c
*/

#include <signal.h>
#include "../includes/Core.hpp"
#include "../includes/Game.hpp"
using namespace ZappyGui;

int main(int ac, char **av) {
    signal(SIGPIPE, SIG_IGN);
    Core core;
    MyRayLib::MyRayLibWindow::MySetTraceLogLevel(LOG_NONE);
    try {
        core.checkArgs(ac, av);
        core.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
