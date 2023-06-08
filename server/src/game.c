/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** game.c
*/

#include "../include/server.h"

char *get_tile_content(zappy_t *zappy, int x, int y)
{
    char *res = malloc(sizeof(char) * (1024 * 4));
    int len = 0;
    if (!res) return NULL;
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
    res[len] = '\0';return res;
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

item_t get_item(char *item)
{
    if (!strncmp(item, "food", 4))
        return FOOD;
    if (!strncmp(item, "linemate", 8))
        return LINEMATE;
    if (!strncmp(item, "deraumere", 9))
        return DERAUMERE;
    if (!strncmp(item, "sibur", 5))
        return SIBUR;
    if (!strncmp(item, "mendiane", 8))
        return MENDIANE;
    if (!strncmp(item, "phiras", 6))
        return PHIRAS;
    if (!strncmp(item, "thystame", 8))
        return THYSTAME;
    return NBR_ITEMS;
}

char *get_item_str(item_t item)
{
    if (item == FOOD)
        return "food";
    if (item == LINEMATE)
        return "linemate";
    if (item == DERAUMERE)
        return "deraumere";
    if (item == SIBUR)
        return "sibur";
    if (item == MENDIANE)
        return "mendiane";
    if (item == PHIRAS)
        return "phiras";
    if (item == THYSTAME)
        return "thystame";
    return NULL;
}

bool check_win(zappy_t *zappy)
{
    if (zappy->game.winningTeam)
        return true;
    for (int i = 0; i < zappy->game.nbrTeams; ++i) {
        player_t *player = zappy->game.teams[i].players;
        int count = 0;
        while (player) {
            (player->level == 8 ? count++ : 0);
            player = player->next;
        }
        if (count >= 6) {
            zappy->game.winningTeam = &zappy->game.teams[i];
            int it = 0;
            notif_guis(it, send_seg(zappy, it, zappy->game.winningTeam));
            return true;
        }
    }
    return false;
}
