/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** pdr.c
*/

#include "../../../include/server.h"

void send_pdr(zappy_t *zappy, int ci, player_t *player, item_t type)
{
    sdprintf(zappy, CLIENT_S(ci), "pdr %d %d\n",
        player->id,
        type
    );
}
