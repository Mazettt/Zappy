/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** right.c
*/

#include "../../../include/server.h"

static void right(zappy_t *zappy, UNUSED char *command, int ci)
{
    player_t *player = zappy->client[ci].player;

    switch (player->direction) {
        case NORTH:
            player->direction = EAST;
            break;
        case EAST:
            player->direction = SOUTH;
            break;
        case SOUTH:
            player->direction = WEST;
            break;
        case WEST:
            player->direction = NORTH;
            break;
    }
    sdprintf(zappy, CLIENT_S(ci), "ok\n");
}

void cmd_right(zappy_t *zappy, char *command, int ci)
{
    add_action(&zappy->client[ci], TIME(7), command, right);
}
