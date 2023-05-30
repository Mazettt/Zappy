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
        for (int j = 0; j < zappy->game.nbrClients; ++j) {
            if (zappy->game.teams[i].players[j].pos_x == x &&
                zappy->game.teams[i].players[j].pos_y == y)
                ++res;
        }
    }
    return res;
}

char *get_tile_content(zappy_t *zappy, int x, int y)
{
    char *res = malloc(sizeof(char) * 1024);
    int len = 0;

    for (int i = 0; i < nbr_players(zappy, x, y); ++i)
        len += sprintf(res + len, " player");
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
