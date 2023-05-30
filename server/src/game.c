/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** game.c
*/

#include "../include/server.h"

bool is_player(zappy_t *zappy, int x, int y)
{
    for (int i = 0; i < zappy->game.nbrTeams; ++i) {
        for (int j = 0; j < zappy->game.nbrClients; ++j) {
            if (zappy->game.teams[i].players[j].pos_x == x &&
                zappy->game.teams[i].players[j].pos_y == y)
                return true;
        }
    }
    return false;
}

void print_map(zappy_t *zappy)
{
    for (int i = 0; i < zappy->game.height; ++i) {
        for (int j = 0; j < zappy->game.width; ++j) {
            printf("%c", is_player(zappy, j, i) ? 'P' : '.');
        }
        printf("\n");
    }
    printf("\n");
}
