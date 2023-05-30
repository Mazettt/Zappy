/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** eject.c
*/

#include "../../../include/server.h"

static void eject(zappy_t *zappy, int ci)
{
    player_t *player = zappy->client[ci].player;
    int movex = player->x;
    int movey = player->y;

    switch (player->direction) {
        case NORTH:
            movey = cast_pos(movey - 1, HEIGHT);
            break;
        case EAST:
            movex = cast_pos(movex + 1, WIDTH);
            break;
        case SOUTH:
            movey = cast_pos(movey + 1, HEIGHT);
            break;
        case WEST:
            movex = cast_pos(movex - 1, WIDTH);
            break;
        default:
            break;
    }
    bool check = false;
    for (int i = 0; i < zappy->game.nbrTeams; ++i) {
        team_t *teamBuff = &zappy->game.teams[i];
        for (int j = 0; j < teamBuff->nbrClients; ++j) {
            player_t *playerBuff = &teamBuff->players[j];
            if (playerBuff->client && playerBuff != zappy->client[ci].player &&
            playerBuff->x == player->x && playerBuff->y == player->y) {
                playerBuff->x = movex;
                playerBuff->y = movey;
                sdprintf(zappy, playerBuff->client->command.s, "eject: %d\n", player->direction); //TODO direction en fonction de la case
                check = true;
            }
        }
    }
    if (check)
        sdprintf(zappy, client_socket(ci), "ok\n");
    else
        sdprintf(zappy, client_socket(ci), "ko\n");
}

void cmd_eject(zappy_t *zappy, char *command, int ci)
{
    (void)command;
    zappy->game.actions = add_action(zappy->game.actions, time_limit(42), ci, eject);
}
