/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** broadcast.c
*/

#include "../../../include/server.h"

static void broadcast(zappy_t *zappy, char *command, int ci)
{
    char *text = command + 10;
    player_t *player = zappy->client[ci].player;
    for (int i = 0; i < zappy->game.nbrTeams; ++i) {
        team_t *teamBuff = &zappy->game.teams[i];
        for (int j = 0; j < teamBuff->nbrClients; ++j) {
            player_t *playerBuff = &teamBuff->players[j];
            if (playerBuff->client && playerBuff != player) {
                sdprintf(zappy, playerBuff->client->command.s,
                    "message %d, %s\n",
                    get_direction(playerBuff->x, playerBuff->y, player->x, player->y, playerBuff->direction),
                    text
                );
            }
        }
    }
}

void cmd_broadcast(zappy_t *zappy, char *command, int ci)
{
    (void)command;
    zappy->game.actions = add_action(zappy->game.actions, time_limit(7), strdup(command), ci, broadcast);
}
