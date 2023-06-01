/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** broadcast.c
*/

#include "../../../include/server.h"

static void notify_guis(zappy_t *zappy, player_t *player, char *message)
{
    for (int i = 0; i < MAX_CONNECTIONS; ++i) {
        if (zappy->client[i].command.s && zappy->client[i].type == GUI)
            send_pbc(zappy, i, player, message);
    }
}

static void broadcast(zappy_t *zappy, char *command, int ci)
{
    char *text = command + 10;
    player_t *player = zappy->client[ci].player;
    notify_guis(zappy, player, text);
    player_t *playerBuff = NULL;
    for (int i = 0, j = 0; (playerBuff = parse_players(zappy, &i, &j));) {
        if (playerBuff->client && playerBuff != player) {
            sdprintf(zappy, playerBuff->client->command.s,
                "message %d, %s\n",
                get_direction(playerBuff->x, playerBuff->y, player->x, player->y, playerBuff->direction),
                text
            );
        }
    }
}

void cmd_broadcast(zappy_t *zappy, char *command, int ci)
{
    (void)command;
    zappy->game.actions = add_action(zappy->game.actions, time_limit(7), strdup(command), ci, broadcast);
}
