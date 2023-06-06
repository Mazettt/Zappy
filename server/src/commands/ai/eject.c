/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** eject.c
*/

#include "../../../include/server.h"

static void destroy_eggs(zappy_t *zappy, player_t *player)
{
    for (int i = 0; i < zappy->game.nbrTeams; ++i) {
        egg_t *egg = zappy->game.teams[i].eggs;
        egg_t *eggBuff = NULL;
        while (egg) {
            eggBuff = egg->next;
            if (egg->x == player->x && egg->y == player->y)
                kill_egg(zappy, egg);
            egg = eggBuff;
        }
    }
}

static void eject(zappy_t *zappy, unused char *command, int ci)
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
    player_t *playerBuff = NULL;
    for (int i = -1; (playerBuff = parse_players(zappy, &i, playerBuff)); playerBuff = playerBuff->next) {
        if (playerBuff->client && playerBuff != player &&
        playerBuff->x == player->x && playerBuff->y == player->y) {
            playerBuff->x = movex;
            playerBuff->y = movey;
            sdprintf(zappy, playerBuff->client->command.s, "eject: %d\n", get_direction(playerBuff->x, playerBuff->y, player->x, player->y, playerBuff->direction));
            notif_guis(send_pex(zappy, notif_it, playerBuff));
            check = true;
        }
    }
    destroy_eggs(zappy, player);
    sdprintf(zappy, client_socket(ci), (check ? "ok\n" : "ko\n"));
}

void cmd_eject(zappy_t *zappy, char *command, int ci)
{
    add_action(&zappy->client[ci], time_limit(7), command, eject);
}
