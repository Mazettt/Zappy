/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** connect_nbr.c
*/

#include "../../../include/server.h"

void cmd_connect_nbr(zappy_t *zappy, unused char *command, int ci)
{
    sdprintf(zappy, client_socket(ci), "%d\n", get_remaining_slots(zappy->client[ci].team));
}
