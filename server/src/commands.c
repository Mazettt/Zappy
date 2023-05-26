/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** commands.c
*/

#include "../include/server.h"
#define commands {  \
    {"stop", stop}, \
    {"noop", noop}, \
    {NULL, NULL}    \
}

void switch_commands(zappy_t *zappy, char *command, int i)
{
    command_t c[] = commands;
    debug_print("com: %s\n", command);
    for (size_t a = 0; c[a].name && c[a].func; ++a)
        if (!strncmp(command, c[a].name, strlen(c[a].name))) {
            (*c[a].func)(zappy, command, i);
            return;
        }
    sdprintf(zappy, client_socket(i), "suc\n"); // unknown command
}
