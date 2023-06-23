/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** game.c
*/

#include "../include/server.h"

static char *fill_tile_content(zappy_t *zappy, int x, int y, char *res)
{
    int len = 0;

    for (int i = 0; i < nbr_players(zappy, x, y); ++i)
        len += sprintf(res + len, "%s%s", (len == 0 ? "" : " "), "player");
    for (int i = 0; i < zappy->game.map[x][y][FOOD]; ++i)
        len += sprintf(res + len, "%s%s", (len == 0 ? "" : " "), "food");
    for (int i = 0; i < zappy->game.map[x][y][LINEMATE]; ++i)
        len += sprintf(res + len, "%s%s", (len == 0 ? "" : " "), "linemate");
    for (int i = 0; i < zappy->game.map[x][y][DERAUMERE]; ++i)
        len += sprintf(res + len, "%s%s", (len == 0 ? "" : " "), "deraumere");
    for (int i = 0; i < zappy->game.map[x][y][SIBUR]; ++i)
        len += sprintf(res + len, "%s%s", (len == 0 ? "" : " "), "sibur");
    for (int i = 0; i < zappy->game.map[x][y][MENDIANE]; ++i)
        len += sprintf(res + len, "%s%s", (len == 0 ? "" : " "), "mendiane");
    for (int i = 0; i < zappy->game.map[x][y][PHIRAS]; ++i)
        len += sprintf(res + len, "%s%s", (len == 0 ? "" : " "), "phiras");
    for (int i = 0; i < zappy->game.map[x][y][THYSTAME]; ++i)
        len += sprintf(res + len, "%s%s", (len == 0 ? "" : " "), "thystame");
    res[len] = '\0';
    return res;
}

char *get_tile_content(zappy_t *zappy, int x, int y)
{
    char *res = malloc(sizeof(char) * (1024 * 4));

    if (!res)
        return NULL;
    return fill_tile_content(zappy, x, y, res);
}

bool check_win(zappy_t *zappy)
{
    player_t *player = NULL;
    int count = 0;
    int it = 0;

    if (zappy->game.winningTeam)
        return true;
    for (int i = 0; i < zappy->game.nbrTeams; ++i) {
        player = zappy->game.teams[i].players;
        count = 0;
        while (player) {
            (player->level == 8 ? count++ : 0);
            player = player->next;
        }
        if (count >= 6) {
            zappy->game.winningTeam = &zappy->game.teams[i];
            NOTIF_GUIS(it, send_seg(zappy, it, zappy->game.winningTeam));
            return true;
        }
    }
    return false;
}

bool init_game(zappy_t *zappy, args_t args)
{
    int nbrTeams = word_array_len(args.teamNames);
    zappy->game.width = args.width;
    zappy->game.height = args.height;
    zappy->game.freq = args.freq;
    zappy->game.teams = malloc(sizeof(team_t) * nbrTeams);
    if (!zappy->game.teams)
        return false;
    zappy->game.nbrTeams = nbrTeams;
    zappy->game.winningTeam = NULL;
    zappy->game.playerIdIt = 0;
    zappy->game.eggIdIt = 0;
    for (int i = 0; i < nbrTeams; ++i) {
        zappy->game.teams[i].name = strdup(args.teamNames[i]);
        zappy->game.teams[i].players = NULL;
        zappy->game.teams[i].eggs = NULL;
        for (int j = 0; j < args.clientsNb; ++j)
            add_egg(zappy, &zappy->game.teams[i]);
    }
    return init_resources(args, &zappy->game);
}
