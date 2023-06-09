/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** pex.c
*/

#include "../../../include/server.h"

void send_pex(zappy_t *zappy, int ci, player_t *player)
{
    sdprintf(zappy, CLIENT_S(ci), "pex %d\n",
        player->id
    );
}
