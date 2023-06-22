/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** resources.c
*/

#include "../include/server.h"

static void fill_resources(args_t args, game_t *game)
{
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
}

static bool init_line_resources(args_t args, game_t *game, int i)
{
    for (int j = 0; j < args.height; ++j) {
        game->map[i][j] = malloc(sizeof(int) * NBR_ITEMS);
        if (!game->map[i][j])
            return false;
        for (int k = 0; k < NBR_ITEMS; ++k)
            game->map[i][j][k] = 0;
    }
    return true;
}

bool init_resources(args_t args, game_t *game)
{
    game->map = malloc(sizeof(int **) * args.width);
    if (!game->map)
        return false;
    for (int i = 0; i < args.width; ++i) {
        game->map[i] = malloc(sizeof(int *) * args.height);
        if (!game->map[i])
            return false;
        if (!init_line_resources(args, game, i))
            return false;
    }
    fill_resources(args, game);
    if (gettimeofday(&game->lastRefill, NULL) == -1)
        return false;
    return true;
}

static void refill(zappy_t *zappy)
{
    for (int i = nbresource(zappy, FOOD); i < (WIDTH * HEIGHT * 0.5); ++i)
        zappy->game.map[rand() % WIDTH][rand() % HEIGHT][FOOD] += 1;
    for (int i = nbresource(zappy, LINEMATE); i < (WIDTH * HEIGHT * 0.3); ++i)
        zappy->game.map[rand() % WIDTH][rand() % HEIGHT][LINEMATE] += 1;
    for (int i = nbresource(zappy, DERAUMERE); i < (WIDTH * HEIGHT * 0.15); ++i)
        zappy->game.map[rand() % WIDTH][rand() % HEIGHT][DERAUMERE] += 1;
    for (int i = nbresource(zappy, SIBUR); i < (WIDTH * HEIGHT * 0.1); ++i)
        zappy->game.map[rand() % WIDTH][rand() % HEIGHT][SIBUR] += 1;
    for (int i = nbresource(zappy, MENDIANE); i < (WIDTH * HEIGHT * 0.1); ++i)
        zappy->game.map[rand() % WIDTH][rand() % HEIGHT][MENDIANE] += 1;
    for (int i = nbresource(zappy, PHIRAS); i < (WIDTH * HEIGHT * 0.08); ++i)
        zappy->game.map[rand() % WIDTH][rand() % HEIGHT][PHIRAS] += 1;
    for (int i = nbresource(zappy, THYSTAME); i < (WIDTH * HEIGHT * 0.05); ++i)
        zappy->game.map[rand() % WIDTH][rand() % HEIGHT][THYSTAME] += 1;
}

void refill_resources(zappy_t *zappy)
{
    struct timeval now;
    int i = 0;

    if (gettimeofday(&now, NULL) == -1)
        return;
    if ((now.tv_sec - zappy->game.lastRefill.tv_sec) * 1000000 +
        (now.tv_usec - zappy->game.lastRefill.tv_usec) < TIME(20))
        return;
    refill(zappy);
    if (gettimeofday(&zappy->game.lastRefill, NULL) == -1)
        return;
    NOTIF_GUIS(i, send_mct(zappy, i));
}
