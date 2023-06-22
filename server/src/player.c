/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** player.c
*/

#include "../include/server.h"

player_t *parse_players(zappy_t *zappy, int *i, player_t *current)
{
    if (!current)
        do {
            ++(*i);
        } while (*i < zappy->game.nbrTeams && !zappy->game.teams[*i].players);
    if (*i >= zappy->game.nbrTeams)
        return NULL;
    return current ? : zappy->game.teams[*i].players;
}

void kill_player(zappy_t *zappy, player_t *player)
{
    int it = 0;

    NOTIF_GUIS(it, send_pdi(zappy, it, player));
    player->client->team = NULL;
    player->client->player = NULL;
    if (player->prev)
        player->prev->next = player->next;
    else
        player->team->players = player->next;
    if (player->next)
        player->next->prev = player->prev;
    free(player);
}

player_t *add_player(zappy_t *zappy, egg_t *egg, client_t *client)
{
    player_t *new = malloc(sizeof(player_t));
    if (!new) return NULL;
    new->id = ++zappy->game.playerIdIt;
    new->x = egg->x;
    new->y = egg->y;
    new->direction = rand() % 4;
    new->level = 1;
    for (int i = 0; i < NBR_ITEMS; ++i)
        new->inventory[i] = (i == FOOD ? 10 : 0);
    new->team = egg->team;
    new->client = client;
    client->team = egg->team;
    client->player = new;
    if (gettimeofday(&new->startTime, NULL) == -1) return NULL;
    new->timeUntilDie = 0;
    new->prev = NULL;
    new->next = egg->team->players;
    if (egg->team->players) egg->team->players->prev = new;
    egg->team->players = new;
    return new;
}

int nbr_players(zappy_t *zappy, int x, int y)
{
    int res = 0;
    player_t *p = NULL;

    for (int i = -1; (p = parse_players(zappy, &i, p)); p = p->next) {
        if (p->x == x && p->y == y && p->client)
            ++res;
    }
    return res;
}

int nbr_players_in_team(team_t *team)
{
    int res = 0;
    player_t *playerBuff = team->players;

    while (playerBuff) {
        ++res;
        playerBuff = playerBuff->next;
    }
    return res;
}
