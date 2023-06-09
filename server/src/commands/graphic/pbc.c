/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** pbc.c
*/

#include "../../../include/server.h"

void send_pbc(zappy_t *zappy, int ci, player_t *player, char *message)
{
    sdprintf(zappy, CLIENT_S(ci), "pbc %d %s\n",
        player->id,
        message
    );
}
