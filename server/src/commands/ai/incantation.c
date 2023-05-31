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

static void toggle_incanting(zappy_t *zappy, player_t *player, bool incanting)
{
    for (int i = 0; i < zappy->game.nbrTeams; ++i) {
        team_t *teamBuff = &zappy->game.teams[i];
        for (int j = 0; j < teamBuff->nbrClients; ++j) {
            player_t *playerBuff = &teamBuff->players[j];
            if (playerBuff->client && playerBuff->x == player->x && playerBuff->y == player->y && playerBuff->level == player->level)
                playerBuff->incanting = incanting;
        }
    }
}

static void rankup_players(zappy_t *zappy, player_t *player)
{
    for (int i = 0; i < zappy->game.nbrTeams; ++i) {
        team_t *teamBuff = &zappy->game.teams[i];
        for (int j = 0; j < teamBuff->nbrClients; ++j) {
            player_t *playerBuff = &teamBuff->players[j];
            if (playerBuff->client && playerBuff->x == player->x && playerBuff->y == player->y && playerBuff->level == player->level)
                sdprintf(zappy, playerBuff->client->command.s, "Current level: %d\n", ++playerBuff->level);
        }
    }
}

static int nbr_players_same_unit_same_lvl(zappy_t *zappy, int lvl, int x, int y)
{
    int res = 0;
    for (int i = 0; i < zappy->game.nbrTeams; ++i) {
        team_t *teamBuff = &zappy->game.teams[i];
        for (int j = 0; j < teamBuff->nbrClients; ++j) {
            player_t *playerBuff = &teamBuff->players[j];
            if (playerBuff->client && playerBuff->level == lvl &&
            playerBuff->x == x && playerBuff->y == y)
                res++;
        }
    }
    return res;
}

static bool check_incantation(zappy_t *zappy, int ci)
{
    player_t *player = zappy->client[ci].player;
    int nbr_players = nbr_players_same_unit_same_lvl(zappy, player->level, player->x, player->y);
    elev_cond_t cond = elev_cond[player->level - 1];

    if (nbr_players != cond.nbr_players)
        return false;
    for (int i = 0; i < NBR_ITEMS; ++i) {
        if (nbr_resource(zappy->game.resources, player->x, player->y, i) < cond.items[i])
            return false;
    }
    return true;
}

static void incantation(zappy_t *zappy, char *command, int ci)
{
    (void)command;
    player_t *player = zappy->client[ci].player;
    if (!player)
        return;
    if (check_incantation(zappy, ci)) {
        elev_cond_t cond = elev_cond[player->level - 1];
        for (int i = 0; i < NBR_ITEMS; ++i) {
            for (int j = 0; j < cond.items[i]; ++j) {
                resource_t *resource = get_resource(zappy->game.resources, player->x, player->y, i);
                remove_resource(&zappy->game.resources, resource);
            }
        }
        rankup_players(zappy, player);
    } else
        sdprintf(zappy, client_socket(ci), "ko\n");
    toggle_incanting(zappy, player, false);
}

void cmd_incantation(zappy_t *zappy, char *command, int ci)
{
    (void)command;
    player_t *player = zappy->client[ci].player;

    zappy->game.actions = add_action(zappy->game.actions, time_limit(300), strdup(command), ci, incantation);
    if (check_incantation(zappy, ci))
        sdprintf(zappy, client_socket(ci), "Elevation underway\n");
    else
        sdprintf(zappy, client_socket(ci), "ko\n");
    toggle_incanting(zappy, player, true);
}
