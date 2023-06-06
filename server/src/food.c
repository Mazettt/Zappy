/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** food.c
*/

#include "../include/server.h"

static void eat_food(zappy_t *zappy, player_t *player)
{
    while (player->inventory[FOOD] > 0) {
        --player->inventory[FOOD];
        player->timeUntilDie += time_limit(126);
    }
}

bool check_food(zappy_t *zappy, player_t *player)
{
    struct timeval now;
    gettimeofday(&now, NULL);
    time_t micro = (now.tv_sec - player->startTime.tv_sec) * 1000000 + now.tv_usec - player->startTime.tv_usec;
    if (micro >= player->timeUntilDie)
        return false;
    eat_food(zappy, player);
    return true;
}
