/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** fork.c
*/

#include "../../../include/server.h"

static void my_fork(zappy_t *zappy, unused char *command, int ci)
{
    team_t *team = zappy->client[ci].team;
    egg_t *newegg = add_egg(zappy, team);
    newegg->x = zappy->client[ci].player->x;
    newegg->y = zappy->client[ci].player->y;
    sdprintf(zappy, client_socket(ci), "ok\n");
    notif_guis(send_enw(zappy, notif_it, zappy->client[ci].player, newegg));
}

void cmd_fork(zappy_t *zappy, char *command, int ci)
{
    add_action(&zappy->client[ci], time_limit(42), command, my_fork);
    notif_guis(send_pfk(zappy, notif_it, zappy->client[ci].player));
}
