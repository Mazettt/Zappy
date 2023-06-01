/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** player.c
*/

#include "../include/server.h"

static void notify_guis(zappy_t *zappy, player_t *player)
{
    for (int i = 0; i < MAX_CONNECTIONS; ++i) {
        if (zappy->client[i].command.s && zappy->client[i].type == GUI)
            send_pdi(zappy, i, player);
    }
}

void kill_player(zappy_t *zappy, player_t *player)
{
    notify_guis(zappy, player);
    player->direction = rand() % 4;
    player->level = 1;
    for (int i = 0; i < NBR_ITEMS; ++i)
        player->inventory[i] = 0;
    player->client->team = NULL;
    player->client->player = NULL;
    player->client = NULL;
    player->incanting = false;
}
