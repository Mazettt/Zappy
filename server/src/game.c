/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** game.c
*/

#include "../include/server.h"

int nbr_players(zappy_t *zappy, int x, int y)
{
    int res = 0;
    for (int i = 0; i < zappy->game.nbrTeams; ++i) {
        for (int j = 0; j < zappy->game.teams[i].nbrClients; ++j) {
            if (zappy->game.teams[i].players[j].x == x &&
                zappy->game.teams[i].players[j].y == y &&
                zappy->game.teams[i].players[j].client)
                ++res;
        }
    }
    return res;
}

char *get_tile_content(zappy_t *zappy, int x, int y)
{
    char *res = malloc(sizeof(char) * (1024 * 4));
    int len = 0;

    for (int i = 0; i < nbr_players(zappy, x, y); ++i)
        len += sprintf(res + len, " player");
    for (int i = 0; i < nbr_resource(zappy->game.resources, x, y, FOOD); ++i)
        len += sprintf(res + len, " food");
    for (int i = 0; i < nbr_resource(zappy->game.resources, x, y, LINEMATE); ++i)
        len += sprintf(res + len, " linemate");
    for (int i = 0; i < nbr_resource(zappy->game.resources, x, y, DERAUMERE); ++i)
        len += sprintf(res + len, " deraumere");
    for (int i = 0; i < nbr_resource(zappy->game.resources, x, y, SIBUR); ++i)
        len += sprintf(res + len, " sibur");
    for (int i = 0; i < nbr_resource(zappy->game.resources, x, y, MENDIANE); ++i)
        len += sprintf(res + len, " mendiane");
    for (int i = 0; i < nbr_resource(zappy->game.resources, x, y, PHIRAS); ++i)
        len += sprintf(res + len, " phiras");
    for (int i = 0; i < nbr_resource(zappy->game.resources, x, y, THYSTAME); ++i)
        len += sprintf(res + len, " thystame");
    res[len] = '\0';
    return res;
}

void print_map(zappy_t *zappy)
{
    for (int i = 0; i < zappy->game.height; ++i) {
        for (int j = 0; j < zappy->game.width; ++j) {
            printf("%c", nbr_players(zappy, j, i) ? 'P' : '.');
        }
        printf("\n");
    }
    printf("\n");
}

int get_direction(int x, int y, int dx, int dy, Direction direction)
{
    if (dx == x && dy == y)
        return 0;
    if (dx == x && dy < y)
        return direction == NORTH ? 1 : direction == SOUTH ? 5 : direction == EAST ? 7 : 3;
    if (dx < x && dy < y)
        return direction == NORTH ? 2 : direction == SOUTH ? 6 : direction == EAST ? 8 : 4;
    if (dx < x && dy == y)
        return direction == NORTH ? 3 : direction == SOUTH ? 7 : direction == EAST ? 1 : 5;
    if (dx < x && dy > y)
        return direction == NORTH ? 4 : direction == SOUTH ? 8 : direction == EAST ? 2 : 6;
    if (dx == x && dy > y)
        return direction == NORTH ? 5 : direction == SOUTH ? 1 : direction == EAST ? 3 : 7;
    if (dx > x && dy > y)
        return direction == NORTH ? 6 : direction == SOUTH ? 2 : direction == EAST ? 4 : 8;
    if (dx > x && dy == y)
        return direction == NORTH ? 7 : direction == SOUTH ? 3 : direction == EAST ? 5 : 1;
    if (dx > x && dy < y)
        return direction == NORTH ? 8 : direction == SOUTH ? 4 : direction == EAST ? 6 : 2;
    return 0;
}
