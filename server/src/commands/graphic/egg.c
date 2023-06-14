/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** enw.c
*/

#include "../../../include/server.h"

void send_egg(zappy_t *zappy, int ci, egg_t *egg)
{
    sdprintf(zappy, CLIENT_S(ci), "egg %d %d %d\n",
        egg->id,
        egg->x,
        egg->y
    );
}

void send_all_eggs(zappy_t *zappy, int ci)
{
    for (int i = 0; i < zappy->game.nbrTeams; ++i) {
        for (egg_t *egg = zappy->game.teams[i].eggs; egg; egg = egg->next)
            send_egg(zappy, ci, egg);
    }
}
