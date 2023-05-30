/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** connect_nbr.c
*/

#include "../../../include/server.h"

void cmd_connect_nbr(zappy_t *zappy, char *command, int ci)
{
    (void)command;
    sdprintf(zappy, client_socket(ci), "%d\n", get_remaining_slots(zappy, zappy->client[ci].team));
}
