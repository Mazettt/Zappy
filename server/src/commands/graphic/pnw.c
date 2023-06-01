/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** pnw.c
*/

#include "../../../include/server.h"

void send_pnw(zappy_t *zappy, int ci, player_t *player)
{
    sdprintf(zappy, client_socket(ci), "pnw %d %d %d %d %d %s\n",
        player->id,
        player->x,
        player->y,
        player->direction + 1,
        player->level,
        player->team->name
    );
}
