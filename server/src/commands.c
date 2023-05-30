/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** commands.c
*/

#include "../include/server.h"
#define commands {  \
    {"stop", stop}, \
    {"noop", noop}, \
    {NULL, NULL}    \
}

static int get_remaining_slots(zappy_t *zappy, team_t *team)
{
    int slots = 0;
    for (int j = 0; j < zappy->game.nbrClients; ++j) {
        if (team->players[j].client == NULL)
            ++slots;
    }
    return slots;
}

static void assign_to_player(zappy_t *zappy, int i, team_t *team)
{
    for (int j = 0; j < zappy->game.nbrClients; ++j) {
        if (team->players[j].client == NULL) {
            team->players[j].client = &zappy->client[i];
            zappy->client[i].player = &team->players[j];
            sdprintf(zappy, client_socket(i), "%d\n%d %d\n", get_remaining_slots(zappy, team), zappy->game.width, zappy->game.height);
            return;
        }
    }
    sdprintf(zappy, client_socket(i), "ko\n");
}

void switch_commands(zappy_t *zappy, char *command, int i)
{
    command_t c[] = commands;
    debug_print("com: %s\n", command);
    for (size_t a = 0; c[a].name && c[a].func; ++a)
        if (!strncmp(command, c[a].name, strlen(c[a].name))) {
            (*c[a].func)(zappy, command, i);
            return;
        }
    if (zappy->client[i].type == UNKNOWN) {
        for (int a = 0; a < zappy->game.nbrTeams; ++a) {
            if (!strcmp(command, zappy->game.teams[a].name)) {
                zappy->client[i].type = AI;
                assign_to_player(zappy, i, &zappy->game.teams[a]);
                return;
            }
        }
    }
    if (zappy->client[i].type == GRAPHIC)
        sdprintf(zappy, client_socket(i), "suc\n");
    else
        sdprintf(zappy, client_socket(i), "ko\n");
}
