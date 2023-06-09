/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** left.c
*/

#include "../../../include/server.h"

static void left(zappy_t *zappy, UNUSED char *command, int ci)
{
    player_t *player = zappy->client[ci].player;

    switch (player->direction) {
        case NORTH:
            player->direction = WEST;
            break;
        case EAST:
            player->direction = NORTH;
            break;
        case SOUTH:
            player->direction = EAST;
            break;
        case WEST:
            player->direction = SOUTH;
            break;
    }
    sdprintf(zappy, CLIENT_S(ci), "ok\n");
}

void cmd_left(zappy_t *zappy, char *command, int ci)
{
    add_action(&zappy->client[ci], TIME(7), command, left);
}
