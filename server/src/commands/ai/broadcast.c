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
    int it = 0;
    notif_guis(it, send_pbc(zappy, it, player, text));
    player_t *p = NULL;
    for (int i = -1; (p = parse_players(zappy, &i, p)); p = p->next) {
        if (p->client && p != player) {
            sdprintf(zappy, p->client->command.s,
                "message %d, %s\n",
                get_direction((pos_t){p->x, p->y},
                    (pos_t){player->x, player->y}, p->direction),
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
