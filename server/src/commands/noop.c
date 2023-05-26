/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** noop.c
*/

#include "../../include/server.h"

void noop(zappy_t *zappy, char *command, int i)
{
    (void)command;
    sdprintf(zappy, client_socket(i), "%s\n", "Command okay.");
}
