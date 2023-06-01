/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** sgt.c
*/

#include "../../../include/server.h"

void cmd_sgt(zappy_t *zappy, char *command, int ci)
{
    (void)command;
    sdprintf(zappy, client_socket(ci), "sgt %d\n", zappy->game.freq);
}
