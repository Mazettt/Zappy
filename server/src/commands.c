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
    {"Set", cmd_set},           \
    {"Broadcast", cmd_broadcast},\
    {"Incantation", cmd_incantation},\
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

static void graphic_begin(zappy_t *zappy, int ci)
{
    sdprintf(zappy, client_socket(ci), "msz %d %d\n", zappy->game.width, zappy->game.height);
    sdprintf(zappy, client_socket(ci), "sgt %d\n", zappy->game.freq);
    for (int x = 0; x < zappy->game.width; ++x)
        for (int y = 0; y < zappy->game.height; ++y)
            sdprintf(zappy, client_socket(ci), "bct %d %d %d %d %d %d %d %d %d\n",
                x, y,
                zappy->game.map[x][y][FOOD],
                zappy->game.map[x][y][LINEMATE],
                zappy->game.map[x][y][DERAUMERE],
                zappy->game.map[x][y][SIBUR],
                zappy->game.map[x][y][MENDIANE],
                zappy->game.map[x][y][PHIRAS],
                zappy->game.map[x][y][THYSTAME]
            );
    for (int i = 0; i < zappy->game.nbrTeams; ++i)
        sdprintf(zappy, client_socket(ci), "tna %s\n", zappy->game.teams[i].name);
}

static void unknown_cmds(zappy_t *zappy, char *command, int ci)
{
    if (!strcmp(command, "GRAPHIC")) {
        zappy->client[ci].type = GRAPHIC;
        graphic_begin(zappy, ci);
        return;
    }
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
