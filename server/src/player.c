/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** player.c
*/

#include "../include/server.h"

void kill_player(zappy_t *zappy, player_t *player)
{
    notif_guis(send_pdi(zappy, notif_it, player));
    player->direction = rand() % 4;
    player->level = 1;
    for (int i = 0; i < NBR_ITEMS; ++i)
        player->inventory[i] = 0;
    player->client->team = NULL;
    player->client->player = NULL;
    player->client = NULL;
    player->incanting = false;
}
