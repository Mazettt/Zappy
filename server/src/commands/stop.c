/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** stop.c
*/

#include "../../include/server.h"

void close_all(zappy_t *zappy)
{
    for (size_t j = 0; j < MAX_CONNECTIONS; ++j)
        close_command_socket(zappy, &zappy->client[j]);
    if (zappy->main.s != 0) {
        shutdown(zappy->main.s, SHUT_RDWR);
        close(zappy->main.s);
        zappy->main.s = 0;
    }
}

void cmd_stop(zappy_t *zappy, char *command, int ci)
{
    (void)command;
    sdprintf(zappy, client_socket(ci), "%s\n", "Server shutting down.");
    close_all(zappy);
}
