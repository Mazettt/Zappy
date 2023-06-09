/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** incantation.c
*/

#include "../../../include/server.h"

static const elev_cond_t elev_cond[] = {
    {1, 1, {0, 1, 0, 0, 0, 0, 0}},
    {2, 2, {0, 1, 1, 1, 0, 0, 0}},
    {3, 2, {0, 2, 0, 1, 0, 2, 0}},
    {4, 4, {0, 1, 1, 2, 0, 1, 0}},
    {5, 4, {0, 1, 2, 1, 3, 0, 0}},
    {6, 6, {0, 1, 2, 3, 0, 1, 0}},
    {7, 6, {0, 2, 2, 2, 2, 2, 1}}
};

static bool check_incantation(zappy_t *zappy, int ci)
{
    player_t *player = zappy->client[ci].player;
    int nbr_players = nbr_players_incantation(zappy, player);
    elev_cond_t cond = elev_cond[player->level - 1];

    if (nbr_players < cond.nbr_players)
        return false;
    for (int i = 0; i < NBR_ITEMS; ++i) {
        if (zappy->game.map[player->x][player->y][i] < cond.items[i])
            return false;
    }
    return true;
}

static void incantation(zappy_t *zappy, UNUSED char *command, int ci)
{
    player_t *player = zappy->client[ci].player;
    int it = 0;

    if (!player)
        return;
    if (check_incantation(zappy, ci)) {
        for (int i = 0; i < NBR_ITEMS; ++i)
            zappy->game.map[player->x][player->y][i] -=
            elev_cond[player->level - 1].items[i];
        rankup_players(zappy, player);
        NOTIF_GUIS(it, send_pie(zappy, it, player, true));
    } else {
        sdprintf(zappy, CLIENT_S(ci), "ko\n");
        NOTIF_GUIS(it, send_pie(zappy, it, player, false));
    }
}

void cmd_incantation(zappy_t *zappy, char *command, int ci)
{
    player_t *player = zappy->client[ci].player;
    player_t **players = NULL;
    int it = 0;

    add_action(&zappy->client[ci], TIME(300), command, incantation);
    if (check_incantation(zappy, ci))
        sdprintf(zappy, CLIENT_S(ci), "Elevation underway\n");
    else
        sdprintf(zappy, CLIENT_S(ci), "ko\n");
    players = get_incantation_players(zappy, player);
    NOTIF_GUIS(it, send_pic(zappy, it, players));
    free(players);
}
