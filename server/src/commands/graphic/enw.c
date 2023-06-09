/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** enw.c
*/

#include "../../../include/server.h"

void send_enw(zappy_t *zappy, int ci, player_t *player, egg_t *egg)
{
    sdprintf(zappy, CLIENT_S(ci), "enw %d %d %d %d\n",
        egg->id,
        player->id,
        player->x,
        player->y
    );
}
