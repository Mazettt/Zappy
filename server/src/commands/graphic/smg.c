/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** smg.c
*/

#include "../../../include/server.h"

void send_smg(zappy_t *zappy, int ci, char *msg)
{
    sdprintf(zappy, client_socket(ci), "smg %s\n", msg);
}
