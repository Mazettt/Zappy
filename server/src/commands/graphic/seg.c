/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** seg.c
*/

#include "../../../include/server.h"

void send_seg(zappy_t *zappy, int ci, team_t *winningTeam)
{
    sdprintf(zappy, client_socket(ci), "seg %s\n",
        winningTeam->name
    );
}
