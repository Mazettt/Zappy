/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** resources.c
*/

#include "../include/server.h"

void init_resources(args_t args, game_t *game)
{
    game->map = malloc(sizeof(int **) * args.width);
    for (int i = 0; i < args.width; ++i) {
        game->map[i] = malloc(sizeof(int *) * args.height);
        for (int j = 0; j < args.height; ++j) {
            game->map[i][j] = malloc(sizeof(int) * NBR_ITEMS);
            for (int k = 0; k < NBR_ITEMS; ++k)
                game->map[i][j][k] = 0;
        }
    }
    for (int i = 0; i < (args.width * args.height * 0.5); ++i)
        game->map[rand() % args.width][rand() % args.height][FOOD] += 1;
    for (int i = 0; i < (args.width * args.height * 0.3); ++i)
        game->map[rand() % args.width][rand() % args.height][LINEMATE] += 1;
    for (int i = 0; i < (args.width * args.height * 0.15); ++i)
        game->map[rand() % args.width][rand() % args.height][DERAUMERE] += 1;
    for (int i = 0; i < (args.width * args.height * 0.1); ++i)
        game->map[rand() % args.width][rand() % args.height][SIBUR] += 1;
    for (int i = 0; i < (args.width * args.height * 0.1); ++i)
        game->map[rand() % args.width][rand() % args.height][MENDIANE] += 1;
    for (int i = 0; i < (args.width * args.height * 0.08); ++i)
        game->map[rand() % args.width][rand() % args.height][PHIRAS] += 1;
    for (int i = 0; i < (args.width * args.height * 0.05); ++i)
        game->map[rand() % args.width][rand() % args.height][THYSTAME] += 1;

    game->map[args.width / 2][args.height / 2][LINEMATE] += 1; //! DEBUG
}
