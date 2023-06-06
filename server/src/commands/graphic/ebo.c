/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** ebo.c
*/

#include "../../../include/server.h"

void send_ebo(zappy_t *zappy, int ci, egg_t *egg)
{
    sdprintf(zappy, client_socket(ci), "ebo %d\n",
        egg->id
    );
}
