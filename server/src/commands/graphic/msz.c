/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** msz.c
*/

#include "../../../include/server.h"

void send_msz(zappy_t *zappy, int ci)
{
    sdprintf(zappy, client_socket(ci), "msz %d %d\n", zappy->game.width, zappy->game.height);
}

void cmd_msz(zappy_t *zappy, char *command, int ci)
{
    (void)command;
    send_msz(zappy, ci);
}
