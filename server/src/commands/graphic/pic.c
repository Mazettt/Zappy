/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** pic.c
*/

#include "../../../include/server.h"

void send_pic(zappy_t *zappy, int ci, player_t **players)
{
    sdprintf(zappy, client_socket(ci), "pic %d %d %d",
        players[0]->x,
        players[0]->y,
        players[0]->level
    );
    for (int i = 0; players[i]; ++i)
        sdprintf(zappy, client_socket(ci), " %d", players[i]->id);
    sdprintf(zappy, client_socket(ci), "\n");
}
