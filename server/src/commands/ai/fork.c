/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** fork.c
*/

#include "../../../include/server.h"

static void my_fork(zappy_t *zappy, int ci)
{
    team_t *team = zappy->client[ci].team;
    team->nbrClients += 1;
    team->players = realloc(team->players, sizeof(player_t) * team->nbrClients);
    player_t *newplayer = &team->players[team->nbrClients - 1];
    newplayer->x = rand() % WIDTH;
    newplayer->y = rand() % HEIGHT;
    newplayer->direction = SOUTH;
    newplayer->level = 1;
    for (int i = 0; i < NBR_ITEMS; ++i)
        newplayer->inventory[i] = 0;
    newplayer->client = NULL;
    sdprintf(zappy, client_socket(ci), "ok\n");
}

void cmd_fork(zappy_t *zappy, char *command, int ci)
{
    (void)command;
    zappy->game.actions = add_action(zappy->game.actions, time_limit(42), ci, my_fork);
}
