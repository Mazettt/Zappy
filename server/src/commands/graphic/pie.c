/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** pie.c
*/

#include "../../../include/server.h"

void send_pie(zappy_t *zappy, int ci, player_t *player, bool result)
{
    sdprintf(zappy, client_socket(ci), "pie %d %d %s\n",
        player->x,
        player->y,
        (result) ? "ok" : "ko"
    );
}
