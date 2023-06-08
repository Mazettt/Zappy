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
    notif_guis(send_pbc(zappy, notif_it, player, text));
    player_t *playerBuff = NULL;
    for (int i = -1; (playerBuff = parse_players(zappy, &i, playerBuff)); playerBuff = playerBuff->next) {
        if (playerBuff->client && playerBuff != player) {
            sdprintf(zappy, playerBuff->client->command.s,
                "message %d, %s\n",
                get_direction(playerBuff->x, playerBuff->y, player->x, player->y, playerBuff->direction),
                text
            );
        }
    }
    sdprintf(zappy, client_socket(ci), "ok\n");
}

void cmd_broadcast(zappy_t *zappy, char *command, int ci)
{
    add_action(&zappy->client[ci], time_limit(7), command, broadcast);
}
