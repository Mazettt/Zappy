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
    team->players = realloc(team->players, sizeof(player_t) * team->nbrClients);
    player_t *newplayer = &team->players[team->nbrClients - 1];
    init_player(&zappy->game, newplayer, team);
    newplayer->x = zappy->client[ci].player->x;
    newplayer->y = zappy->client[ci].player->y;
    newplayer->direction = rand() % 4;
    sdprintf(zappy, client_socket(ci), "ok\n");
    notif_guis(send_enw(zappy, notif_it, zappy->client[ci].player, newplayer));
}

void cmd_fork(zappy_t *zappy, char *command, int ci)
{
    (void)command;
    add_action(&zappy->client[ci], time_limit(42), command, my_fork);
    notif_guis(send_pfk(zappy, notif_it, zappy->client[ci].player));
}
