/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** forward.c
*/

#include "../../../include/server.h"

static void forward(zappy_t *zappy, UNUSED char *command, int ci)
{
    player_t *player = zappy->client[ci].player;
    int it = 0;

    switch (player->direction) {
        case NORTH:
            player->y = CAST_POS(player->y - 1, HEIGHT);
            break;
        case EAST:
            player->x = CAST_POS(player->x + 1, WIDTH);
            break;
        case SOUTH:
            player->y = CAST_POS(player->y + 1, HEIGHT);
            break;
        case WEST:
            player->x = CAST_POS(player->x - 1, WIDTH);
            break;
    }
    NOTIF_GUIS(it, send_ppo(zappy, it, player));
    sdprintf(zappy, CLIENT_S(ci), "ok\n");
}

void cmd_forward(zappy_t *zappy, char *command, int ci)
{
    add_action(&zappy->client[ci], TIME(7), command, forward);
}
