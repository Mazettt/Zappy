/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** edi.c
*/

#include "../../../include/server.h"

void send_edi(zappy_t *zappy, int ci, egg_t *egg)
{
    sdprintf(zappy, CLIENT_S(ci), "edi %d\n",
        egg->id
    );
}
