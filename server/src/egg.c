/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** egg.c
*/

#include "../include/server.h"

egg_t *add_egg(zappy_t *zappy, player_t *player)
{
    egg_t *new = malloc(sizeof(egg_t));
    new->id = ++zappy->game.eggIdIt;
    new->x = player->x;
    new->y = player->y;
    new->team = player->team;
    new->player = player;

    new->prev = NULL;
    new->next = player->team->eggs;
    player->team->eggs = new;
    return new;
}

void kill_egg(zappy_t *zappy, egg_t *egg)
{
    // notif_guis(send_edi);
    egg->team->nbrClients--;

    if (egg->prev)
        egg->prev->next = egg->next;
    else
        egg->team->eggs = egg->next;
    if (egg->next)
        egg->next->prev = egg->prev;
    free(egg);
}

int nbr_eggs_in_team(team_t *team)
{
    int res = 0;
    egg_t *eggBuff = team->eggs;
    while (eggBuff) {
        ++res;
        eggBuff = eggBuff->next;
    }
    return res;
}
