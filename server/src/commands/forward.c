/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** forward.c
*/

#include "../../include/server.h"

static void forward(zappy_t *zappy, int i)
{
    player_t *player = zappy->client[i].player;
    switch (player->direction) {
        case NORTH:
            player->pos_y = (player->pos_y - 1) % zappy->game.height;
            break;
        case EAST:
            player->pos_x = (player->pos_x + 1) % zappy->game.width;
            break;
        case SOUTH:
            player->pos_y = (player->pos_y + 1) % zappy->game.height;
            break;
        case WEST:
            player->pos_x = (player->pos_x - 1) % zappy->game.width;
            break;
    }
    sdprintf(zappy, client_socket(i), "Player moved forward\n");
}

void cmd_forward(zappy_t *zappy, char *command, int i)
{
    (void)command;
    zappy->game.actions = add_action(zappy->game.actions, time_limit(7), i, forward);
    sdprintf(zappy, client_socket(i), "ok\n");
}
