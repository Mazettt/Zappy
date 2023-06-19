/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** incantation_utils.c
*/

#include "../../../include/server.h"

static bool can_incant(player_t *player, player_t *basePlayer)
{
    return player->client && player->x == basePlayer->x &&
        player->y == basePlayer->y && player->level == basePlayer->level;
}

void rankup_players(zappy_t *zappy, player_t *basePlayer)
{
    player_t backupBasePlayer = *basePlayer;
    player_t *p = NULL;
    int it = 0;

    for (int i = -1; (p = parse_players(zappy, &i, p)); p = p->next) {
        if (can_incant(p, &backupBasePlayer)) {
            sdprintf(zappy, p->client->command.s, "Current level: %d\n",
                ++p->level);
            NOTIF_GUIS(it, send_plv(zappy, it, p));
        }
    }
}

int nbr_players_incantation(zappy_t *zappy, player_t *basePlayer)
{
    int res = 0;
    player_t *p = NULL;

    for (int i = -1; (p = parse_players(zappy, &i, p)); p = p->next) {
        if (can_incant(p, basePlayer))
            res++;
    }
    return res;
}

player_t **get_incantation_players(zappy_t *zappy, player_t *basePlayer)
{
    player_t **players = malloc(sizeof(player_t *) *
        (nbr_players_incantation(zappy, basePlayer) + 1));
    player_t *p = NULL;
    int index = 0;

    if (!players)
        return NULL;
    for (int i = -1; (p = parse_players(zappy, &i, p)); p = p->next)
        if (can_incant(p, basePlayer))
            players[index++] = p;
    players[index] = NULL;
    return players;
}
