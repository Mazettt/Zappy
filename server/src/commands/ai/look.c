/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** look.c
*/

#include "../../../include/server.h"

static void look(zappy_t *zappy, UNUSED char *command, int ci)
{
    player_t *player = zappy->client[ci].player;

    switch (player->direction) {
        case NORTH:
            look_north(zappy, ci);
            break;
        case EAST:
            look_east(zappy, ci);
            break;
        case SOUTH:
            look_south(zappy, ci);
            break;
        case WEST:
            look_west(zappy, ci);
            break;
    }
}

void cmd_look(zappy_t *zappy, char *command, int ci)
{
    add_action(&zappy->client[ci], TIME(7), command, look);
}
