/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** tna.c
*/

#include "../../../include/server.h"

void send_tna(zappy_t *zappy, int ci)
{
    for (int i = 0; i < zappy->game.nbrTeams; ++i)
        sdprintf(zappy, client_socket(ci), "tna %s\n",
            zappy->game.teams[i].name);
}

void cmd_tna(zappy_t *zappy, unused char *command, int ci)
{
    send_tna(zappy, ci);
}
