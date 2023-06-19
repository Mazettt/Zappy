/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** eject.c
*/

#include "../../../include/server.h"

static void destroy_eggs(zappy_t *zappy, player_t *player)
{
    egg_t *egg = NULL;
    egg_t *eggBuff = NULL;

    for (int i = 0; i < zappy->game.nbrTeams; ++i) {
        egg = zappy->game.teams[i].eggs;
        eggBuff = NULL;
        while (egg) {
            eggBuff = egg->next;
            (egg->x == player->x && egg->y == player->y) ?
                kill_egg(zappy, egg) : 0;
            egg = eggBuff;
        }
    }
}

static pos_t get_move(zappy_t *zappy, player_t *player)
{
    pos_t move = {player->x, player->y};

    switch (player->direction) {
        case NORTH:
            move.y = CAST_POS(move.y - 1, HEIGHT);
            break;
        case EAST:
            move.x = CAST_POS(move.x + 1, WIDTH);
            break;
        case SOUTH:
            move.y = CAST_POS(move.y + 1, HEIGHT);
            break;
        case WEST:
            move.x = CAST_POS(move.x - 1, WIDTH);
            break;
        default:
            break;
    }
    return move;
}

static void eject(zappy_t *zappy, UNUSED char *command, int ci)
{
    player_t *cp = zappy->client[ci].player;
    pos_t move = get_move(zappy, cp);
    bool check = false;
    player_t *p = NULL;
    int it = 0;
    NOTIF_GUIS(it, send_pex(zappy, it, cp));
    it = 0;
    for (int i = -1; (p = parse_players(zappy, &i, p)); p = p->next) {
        if (p->client && p != cp &&
        p->x == cp->x && p->y == cp->y) {
            p->x = move.x;
            p->y = move.y;
            sdprintf(zappy, p->client->command.s, "eject: %d\n", get_direction(
            zappy, (pos_t){p->x, p->y}, (pos_t){cp->x, cp->y}, p->direction));
            NOTIF_GUIS(it, send_ppo(zappy, it, p));
            check = true;
        }
    }
    destroy_eggs(zappy, cp);
    sdprintf(zappy, CLIENT_S(ci), (check ? "ok\n" : "ko\n"));
}

void cmd_eject(zappy_t *zappy, char *command, int ci)
{
    add_action(&zappy->client[ci], TIME(7), command, eject);
}
