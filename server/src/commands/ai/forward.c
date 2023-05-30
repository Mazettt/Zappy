/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** forward.c
*/

#include "../../../include/server.h"

static void forward(zappy_t *zappy, int ci)
{
    player_t *player = zappy->client[ci].player;
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
    sdprintf(zappy, client_socket(ci), "Player is now in %d %d\n", player->pos_x, player->pos_y);
}

void cmd_forward(zappy_t *zappy, char *command, int ci)
{
    (void)command;
    zappy->game.actions = add_action(zappy->game.actions, time_limit(7), ci, forward);
    sdprintf(zappy, client_socket(ci), "ok\n");
}
