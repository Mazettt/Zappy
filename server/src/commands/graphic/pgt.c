/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** pgt.c
*/

#include "../../../include/server.h"

void send_pgt(zappy_t *zappy, int ci, player_t *player, item_t type)
{
    sdprintf(zappy, CLIENT_S(ci), "pgt %d %d\n",
        player->id,
        type
    );
}
