/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** noop.c
*/

#include "../../include/server.h"

void cmd_noop(zappy_t *zappy, UNUSED char *command, int ci)
{
    sdprintf(zappy, CLIENT_S(ci), "%s\n", "Command okay.");
}
