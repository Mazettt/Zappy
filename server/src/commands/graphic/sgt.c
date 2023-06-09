/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** sgt.c
*/

#include "../../../include/server.h"

void send_sgt(zappy_t *zappy, int ci)
{
    sdprintf(zappy, CLIENT_S(ci), "sgt %d\n", zappy->game.freq);
}

void cmd_sgt(zappy_t *zappy, UNUSED char *command, int ci)
{
    send_sgt(zappy, ci);
}
