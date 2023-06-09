/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** pfk.c
*/

#include "../../../include/server.h"

void send_pfk(zappy_t *zappy, int ci, player_t *player)
{
    sdprintf(zappy, CLIENT_S(ci), "pfk %d\n",
        player->id
    );
}
