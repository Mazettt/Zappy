/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** right.c
*/

#include "../../../include/server.h"

static void right(zappy_t *zappy, int ci)
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
    sdprintf(zappy, client_socket(ci), "Player is now facing %s\n", player->direction == NORTH ? "North" : player->direction == EAST ? "East" : player->direction == SOUTH ? "South" : "West");
}

void cmd_right(zappy_t *zappy, char *command, int ci)
{
    (void)command;
    zappy->game.actions = add_action(zappy->game.actions, time_limit(7), ci, right);
    sdprintf(zappy, client_socket(ci), "ok\n");
}
