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
            player->y = cast_pos(player->y - 1, HEIGHT);
            break;
        case EAST:
            player->x = cast_pos(player->x + 1, WIDTH);
            break;
        case SOUTH:
            player->y = cast_pos(player->y + 1, HEIGHT);
            break;
        case WEST:
            player->x = cast_pos(player->x - 1, WIDTH);
            break;
    }
    sdprintf(zappy, client_socket(ci), "ok\n");
    sdprintf(zappy, client_socket(ci), "Player is now in %d %d\n", player->x, player->y); //! DEBUG
}

void cmd_forward(zappy_t *zappy, char *command, int ci)
{
    (void)command;
    zappy->game.actions = add_action(zappy->game.actions, time_limit(7), ci, forward);
}
