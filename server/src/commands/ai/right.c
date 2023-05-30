/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** right.c
*/

#include "../../../include/server.h"

static void right(zappy_t *zappy, int i)
{
    player_t *player = zappy->client[i].player;
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
    sdprintf(zappy, client_socket(i), "Player is now facing %s\n", player->direction == NORTH ? "North" : player->direction == EAST ? "East" : player->direction == SOUTH ? "South" : "West");
}

void cmd_right(zappy_t *zappy, char *command, int i)
{
    (void)command;
    zappy->game.actions = add_action(zappy->game.actions, time_limit(7), i, right);
    sdprintf(zappy, client_socket(i), "ok\n");
}
