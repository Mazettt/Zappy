/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** mct.c
*/

#include "../../../include/server.h"

void send_mct(zappy_t *zappy, int ci)
{
    for (int x = 0; x < zappy->game.width; ++x)
        for (int y = 0; y < zappy->game.height; ++y)
            send_bct(zappy, ci, x, y);
}

void cmd_mct(zappy_t *zappy, char *command, int ci)
{
    (void)command;
    send_mct(zappy, ci);
}
