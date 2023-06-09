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
        len += sprintf(res + len, " player");
    for (int i = 0; i < zappy->game.map[x][y][FOOD]; ++i)
        len += sprintf(res + len, " food");
    for (int i = 0; i < zappy->game.map[x][y][LINEMATE]; ++i)
        len += sprintf(res + len, " linemate");
    for (int i = 0; i < zappy->game.map[x][y][DERAUMERE]; ++i)
        len += sprintf(res + len, " deraumere");
    for (int i = 0; i < zappy->game.map[x][y][SIBUR]; ++i)
        len += sprintf(res + len, " sibur");
    for (int i = 0; i < zappy->game.map[x][y][MENDIANE]; ++i)
        len += sprintf(res + len, " mendiane");
    for (int i = 0; i < zappy->game.map[x][y][PHIRAS]; ++i)
        len += sprintf(res + len, " phiras");
    for (int i = 0; i < zappy->game.map[x][y][THYSTAME]; ++i)
        len += sprintf(res + len, " thystame");
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

int get_direction(pos_t p, pos_t dp, Direction d)
{
    if (dp.x == p.x && dp.y == p.y)
        return 0;
    if (dp.x == p.x && dp.y < p.y)
        return d == NORTH ? 1 : d == SOUTH ? 5 : d == EAST ? 7 : 3;
    if (dp.x < p.x && dp.y < p.y)
        return d == NORTH ? 2 : d == SOUTH ? 6 : d == EAST ? 8 : 4;
    if (dp.x < p.x && dp.y == p.y)
        return d == NORTH ? 3 : d == SOUTH ? 7 : d == EAST ? 1 : 5;
    if (dp.x < p.x && dp.y > p.y)
        return d == NORTH ? 4 : d == SOUTH ? 8 : d == EAST ? 2 : 6;
    if (dp.x == p.x && dp.y > p.y)
        return d == NORTH ? 5 : d == SOUTH ? 1 : d == EAST ? 3 : 7;
    if (dp.x > p.x && dp.y > p.y)
        return d == NORTH ? 6 : d == SOUTH ? 2 : d == EAST ? 4 : 8;
    if (dp.x > p.x && dp.y == p.y)
        return d == NORTH ? 7 : d == SOUTH ? 3 : d == EAST ? 5 : 1;
    if (dp.x > p.x && dp.y < p.y)
        return d == NORTH ? 8 : d == SOUTH ? 4 : d == EAST ? 6 : 2;
    return 0;
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
