/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** commands.c
*/

#include "../include/server.h"
#define ai_commands {           \
    {"stop", cmd_stop},         \
    {"noop", cmd_noop},         \
    {"Forward", cmd_forward},   \
    {NULL, NULL}                \
}
#define graphic_commands {      \
    {NULL, NULL}                \
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

static void ai_cmds(zappy_t *zappy, char *command, int i)
{
    command_t c[] = ai_commands;
    for (size_t a = 0; c[a].name && c[a].func; ++a)
        if (!strncmp(command, c[a].name, strlen(c[a].name))) {
            (*c[a].func)(zappy, command, i);
            return;
        }
    sdprintf(zappy, client_socket(i), "ko\n");
}

static void graphic_cmds(zappy_t *zappy, char *command, int i)
{
    command_t c[] = graphic_commands;
    for (size_t a = 0; c[a].name && c[a].func; ++a)
        if (!strncmp(command, c[a].name, strlen(c[a].name))) {
            (*c[a].func)(zappy, command, i);
            return;
        }
    sdprintf(zappy, client_socket(i), "suc\n");
}

static void unknown_cmds(zappy_t *zappy, char *command, int i)
{
    for (int a = 0; a < zappy->game.nbrTeams; ++a) {
        if (!strcmp(command, zappy->game.teams[a].name)) {
            zappy->client[i].type = AI;
            assign_to_player(zappy, i, &zappy->game.teams[a]);
            return;
        }
    }
    sdprintf(zappy, client_socket(i), "ko\n");
}

void switch_commands(zappy_t *zappy, char *command, int i)
{
    debug_print("com: %s\n", command);
    if (zappy->client[i].type == AI)
        ai_cmds(zappy, command, i);
    else if (zappy->client[i].type == GRAPHIC)
        graphic_cmds(zappy, command, i);
    else if (zappy->client[i].type == UNKNOWN)
        unknown_cmds(zappy, command, i);
}
