/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** fork.c
*/

#include "../../../include/server.h"

static void my_fork(zappy_t *zappy, UNUSED char *command, int ci)
{
    team_t *team = zappy->client[ci].team;
    egg_t *newegg = add_egg(zappy, team);

    if (!newegg) {
        sdprintf(zappy, CLIENT_S(ci), "ko\n");
        return;
    }
    newegg->x = zappy->client[ci].player->x;
    newegg->y = zappy->client[ci].player->y;
    sdprintf(zappy, CLIENT_S(ci), "ok\n");
    int it = 0;
    NOTIF_GUIS(it, send_enw(zappy, it, zappy->client[ci].player, newegg));
}

void cmd_fork(zappy_t *zappy, char *command, int ci)
{
    int it = 0;

    add_action(&zappy->client[ci], TIME(42), command, my_fork);
    NOTIF_GUIS(it, send_pfk(zappy, it, zappy->client[ci].player));
}
