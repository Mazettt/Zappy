/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** seg.c
*/

#include "../../../include/server.h"

void send_seg(zappy_t *zappy, int ci, team_t *winningTeam)
{
    sdprintf(zappy, CLIENT_S(ci), "seg %s\n",
        winningTeam->name
    );
}
