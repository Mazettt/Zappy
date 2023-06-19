/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** broadcast.c
*/

#include "../../../include/server.h"

static void broadcast(zappy_t *zappy, char *command, int ci)
{
    char *text = NULL;
    player_t *player = zappy->client[ci].player;
    int it = 0;
    player_t *p = NULL;

    if (strlen(command) < 11)
        return sdprintf(zappy, CLIENT_S(ci), "ko\n");
    text = command + 10;
    NOTIF_GUIS(it, send_pbc(zappy, it, player, text));
    for (int i = -1; (p = parse_players(zappy, &i, p)); p = p->next) {
        if (p->client && p != player) {
            sdprintf(zappy, p->client->command.s,
                "message %d, %s\n",
                get_direction(zappy, (pos_t){p->x, p->y},
                    (pos_t){player->x, player->y}, p->direction),
                text
            );
        }
    }
    sdprintf(zappy, CLIENT_S(ci), "ok\n");
}

void cmd_broadcast(zappy_t *zappy, char *command, int ci)
{
    add_action(&zappy->client[ci], TIME(7), command, broadcast);
}
