/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** pic.c
*/

#include "../../../include/server.h"

void send_pic(zappy_t *zappy, int ci, player_t **players)
{
    if (!players)
        return;
    sdprintf(zappy, CLIENT_S(ci), "pic %d %d %d",
        players[0]->x,
        players[0]->y,
        players[0]->level
    );
    for (int i = 0; players[i]; ++i)
        sdprintf(zappy, CLIENT_S(ci), " %d", players[i]->id);
    sdprintf(zappy, CLIENT_S(ci), "\n");
}
