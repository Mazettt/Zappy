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
    (void)ac;
    (void)av;
    Core _core;
    // try {
    //     _core.checkArgs(ac, av);
    //     _core.handleConnectionServer();
    // } catch (const std::exception &e) {
    //     std::cerr << e.what() << std::endl;
    //     return 84;
    // }

    Game game(10, 10);
    game.initialize();
    game.run();
    return 0;
}
