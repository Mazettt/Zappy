/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** pdi.c
*/

#include "../../../include/server.h"

void send_pdi(zappy_t *zappy, int ci, player_t *player)
{
    sdprintf(zappy, client_socket(ci), "pdi %d\n",
        player->id
    );
}
