/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** forward.c
*/

#include "../../../include/server.h"

static void forward(zappy_t *zappy, unused char *command, int ci)
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
    int it = 0;
    notif_guis(it, send_ppo(zappy, it, player));
    sdprintf(zappy, client_socket(ci), "ok\n");
}

void cmd_forward(zappy_t *zappy, char *command, int ci)
{
    add_action(&zappy->client[ci], time_limit(7), command, forward);
}
