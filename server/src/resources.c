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

    gettimeofday(&game->lastRefill, NULL);
}

int nbr_resources(zappy_t *zappy, Item type)
{
    int nbr = 0;
    for (int i = 0; i < zappy->game.width; ++i)
        for (int j = 0; j < zappy->game.height; ++j)
            nbr += zappy->game.map[i][j][type];
    return nbr;
}

void refill_resources(zappy_t *zappy)
{
    struct timeval now;
    gettimeofday(&now, NULL);
    time_t micro = (now.tv_sec - zappy->game.lastRefill.tv_sec) * 1000000 + now.tv_usec - zappy->game.lastRefill.tv_usec;
    if (micro < time_limit(20))
        return;
    for (int i = nbr_resources(zappy, FOOD); i < (zappy->game.width * zappy->game.height * 0.5); ++i)
        zappy->game.map[rand() % zappy->game.width][rand() % zappy->game.height][FOOD] += 1;
    for (int i = nbr_resources(zappy, LINEMATE); i < (zappy->game.width * zappy->game.height * 0.3); ++i)
        zappy->game.map[rand() % zappy->game.width][rand() % zappy->game.height][LINEMATE] += 1;
    for (int i = nbr_resources(zappy, DERAUMERE); i < (zappy->game.width * zappy->game.height * 0.15); ++i)
        zappy->game.map[rand() % zappy->game.width][rand() % zappy->game.height][DERAUMERE] += 1;
    for (int i = nbr_resources(zappy, SIBUR); i < (zappy->game.width * zappy->game.height * 0.1); ++i)
        zappy->game.map[rand() % zappy->game.width][rand() % zappy->game.height][SIBUR] += 1;
    for (int i = nbr_resources(zappy, MENDIANE); i < (zappy->game.width * zappy->game.height * 0.1); ++i)
        zappy->game.map[rand() % zappy->game.width][rand() % zappy->game.height][MENDIANE] += 1;
    for (int i = nbr_resources(zappy, PHIRAS); i < (zappy->game.width * zappy->game.height * 0.08); ++i)
        zappy->game.map[rand() % zappy->game.width][rand() % zappy->game.height][PHIRAS] += 1;
    for (int i = nbr_resources(zappy, THYSTAME); i < (zappy->game.width * zappy->game.height * 0.05); ++i)
        zappy->game.map[rand() % zappy->game.width][rand() % zappy->game.height][THYSTAME] += 1;
    gettimeofday(&zappy->game.lastRefill, NULL);
}
