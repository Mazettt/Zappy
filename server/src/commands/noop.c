/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** noop.c
*/

#include "../../include/server.h"

void cmd_noop(zappy_t *zappy, char *command, int ci)
{
    (void)command;
    sdprintf(zappy, client_socket(ci), "%s\n", "Command okay.");
}
