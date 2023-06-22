/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** food.c
*/

#include "../include/server.h"

static bool eat_food(zappy_t *zappy, player_t *player)
{
    if (player->inventory[FOOD] > 0) {
        --player->inventory[FOOD];
        player->timeUntilDie += TIME(126);
        return true;
    }
    return false;
}

bool check_food(zappy_t *zappy, player_t *player)
{
    struct timeval now;

    if (gettimeofday(&now, NULL) == -1)
        return false;
    if ((now.tv_sec - player->startTime.tv_sec) * 1000000 +
        (now.tv_usec - player->startTime.tv_usec) >= player->timeUntilDie) {
        return eat_food(zappy, player);
    }
    return true;
}
