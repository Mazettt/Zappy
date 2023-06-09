/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** sbp.c
*/

#include "../../../include/server.h"

void send_sbp(zappy_t *zappy, int ci)
{
    sdprintf(zappy, CLIENT_S(ci), "sbp\n");
}
