/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** fork.c
*/

#include "../../../include/server.h"

static void my_fork(zappy_t *zappy, char *command, int ci)
{
    (void)command;
    team_t *team = zappy->client[ci].team;
    team->nbrClients += 1;
    egg_t *newegg = add_egg(zappy, zappy->client[ci].player);
    sdprintf(zappy, client_socket(ci), "ok\n");
    notif_guis(send_enw(zappy, notif_it, zappy->client[ci].player, newegg));
}

void cmd_fork(zappy_t *zappy, char *command, int ci)
{
    (void)command;
    add_action(&zappy->client[ci], time_limit(42), command, my_fork);
    notif_guis(send_pfk(zappy, notif_it, zappy->client[ci].player));
}
