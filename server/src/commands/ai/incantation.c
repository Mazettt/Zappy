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

static bool can_incant(player_t *player, player_t *basePlayer)
{
    return player->client && player->x == basePlayer->x && player->y == basePlayer->y && player->level == basePlayer->level;
}

static void toggle_incanting(zappy_t *zappy, player_t *basePlayer, bool incanting)
{
    player_t *playerBuff = NULL;
    for (int i = 0, j = 0; (playerBuff = parse_players(zappy, &i, &j));) {
        if (can_incant(playerBuff, basePlayer))
            playerBuff->incanting = incanting;
    }
}

static void rankup_players(zappy_t *zappy, player_t *basePlayer)
{
    player_t backupBasePlayer = *basePlayer;
    player_t *playerBuff = NULL;
    for (int i = 0, j = 0; (playerBuff = parse_players(zappy, &i, &j));) {
        if (can_incant(playerBuff, &backupBasePlayer))
            sdprintf(zappy, playerBuff->client->command.s, "Current level: %d\n", ++playerBuff->level);
    }
}

static int nbr_players_incantation(zappy_t *zappy, player_t *basePlayer)
{
    int res = 0;
    player_t *playerBuff = NULL;
    for (int i = 0, j = 0; (playerBuff = parse_players(zappy, &i, &j));) {
        if (can_incant(playerBuff, basePlayer))
            res++;
    }
    return res;
}

static player_t **get_incantation_players(zappy_t *zappy, player_t *basePlayer)
{
    player_t **players = malloc(sizeof(player_t *) * (nbr_players_incantation(zappy, basePlayer) + 1));
    int index = 0;
    player_t *playerBuff = NULL;
    for (int i = 0, j = 0; (playerBuff = parse_players(zappy, &i, &j));)
        if (can_incant(playerBuff, basePlayer))
            players[index++] = playerBuff;
    players[index] = NULL;
    return players;
}

static bool check_incantation(zappy_t *zappy, int ci)
{
    player_t *player = zappy->client[ci].player;
    int nbr_players = nbr_players_incantation(zappy, player);
    elev_cond_t cond = elev_cond[player->level - 1];

    if (nbr_players < cond.nbr_players)
        return false;
    for (int i = 0; i < NBR_ITEMS; ++i) {
        if (zappy->game.map[player->x][player->y][i] < cond.items[i])
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
        for (int i = 0; i < NBR_ITEMS; ++i)
            zappy->game.map[player->x][player->y][i] -= cond.items[i];
        rankup_players(zappy, player);
    } else
        sdprintf(zappy, client_socket(ci), "ko\n");
    toggle_incanting(zappy, player, false);
}

static void notify_guis(zappy_t *zappy, player_t **players)
{
    for (int i = 0; i < MAX_CONNECTIONS; ++i) {
        if (zappy->client[i].command.s && zappy->client[i].type == GUI)
            send_pic(zappy, i, players);
    }
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
    player_t **players = get_incantation_players(zappy, player);
    notify_guis(zappy, players);
    free(players);
}
