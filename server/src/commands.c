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
    {"Right", cmd_right},       \
    {"Left", cmd_left},         \
    {"Look", cmd_look},         \
    {"Inventory", cmd_inventory},\
    {"Connect_nbr", cmd_connect_nbr},\
    {"Fork", cmd_fork},         \
    {"Eject", cmd_eject},       \
    {"Take", cmd_take},         \
    {NULL, NULL}                \
}
#define graphic_commands {      \
    {"stop", cmd_stop},         \
    {"noop", cmd_noop},         \
    {NULL, NULL}                \
}

static void assign_to_player(zappy_t *zappy, int ci, team_t *team)
{
    for (int j = 0; j < team->nbrClients; ++j) {
        if (team->players[j].client == NULL) {
            team->players[j].client = &zappy->client[ci];
            zappy->client[ci].team = team;
            zappy->client[ci].player = &team->players[j];
            sdprintf(zappy, client_socket(ci), "%d\n%d %d\n", get_remaining_slots(team), zappy->game.width, zappy->game.height);
            return;
        }
    }
    sdprintf(zappy, client_socket(ci), "ko\n");
}

static void ai_cmds(zappy_t *zappy, char *command, int ci)
{
    command_t c[] = ai_commands;
    for (size_t a = 0; c[a].name && c[a].func; ++a)
        if (!strncmp(command, c[a].name, strlen(c[a].name))) {
            (*c[a].func)(zappy, command, ci);
            return;
        }
    sdprintf(zappy, client_socket(ci), "ko\n");
}

static void graphic_cmds(zappy_t *zappy, char *command, int ci)
{
    command_t c[] = graphic_commands;
    for (size_t a = 0; c[a].name && c[a].func; ++a)
        if (!strncmp(command, c[a].name, strlen(c[a].name))) {
            (*c[a].func)(zappy, command, ci);
            return;
        }
    sdprintf(zappy, client_socket(ci), "suc\n");
}

static void unknown_cmds(zappy_t *zappy, char *command, int ci)
{
    for (int a = 0; a < zappy->game.nbrTeams; ++a) {
        if (!strcmp(command, zappy->game.teams[a].name)) {
            zappy->client[ci].type = AI;
            assign_to_player(zappy, ci, &zappy->game.teams[a]);
            return;
        }
    }
    sdprintf(zappy, client_socket(ci), "ko\n");
}

void switch_commands(zappy_t *zappy, char *command, int ci)
{
    debug_print("com: %s\n", command);
    if (zappy->client[ci].type == AI)
        ai_cmds(zappy, command, ci);
    else if (zappy->client[ci].type == GRAPHIC)
        graphic_cmds(zappy, command, ci);
    else if (zappy->client[ci].type == UNKNOWN)
        unknown_cmds(zappy, command, ci);
}
