/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** commands.c
*/

#include "../include/server.h"

static const command_t ai_cmds[] = {
    {"Forward", cmd_forward},
    {"Right", cmd_right},
    {"Left", cmd_left},
    {"Look", cmd_look},
    {"Inventory", cmd_inventory},
    {"Connect_nbr", cmd_connect_nbr},
    {"Fork", cmd_fork},
    {"Eject", cmd_eject},
    {"Take", cmd_take},
    {"Set", cmd_set},
    {"Broadcast", cmd_broadcast},
    {"Incantation", cmd_incantation},
    {NULL, NULL}
};

static const command_t gui_cmds[] = {
    {"msz", cmd_msz},
    {"sgt", cmd_sgt},
    {"sst", cmd_sst},
    {"bct", cmd_bct},
    {"mct", cmd_mct},
    {"tna", cmd_tna},
    {"ppo", cmd_ppo},
    {"plv", cmd_plv},
    {"pin", cmd_pin},
    {NULL, NULL}
};

static void assign_to_player(zappy_t *zappy, int ci, team_t *team)
{
    player_t *new = NULL;
    int it = 0;

    if (team->eggs) {
        new = hatch_egg(zappy, team->eggs, &zappy->client[ci]);
        if (!new)
            return sdprintf(zappy, CLIENT_S(ci), "ko\n");
        sdprintf(zappy, CLIENT_S(ci), "%d\n%d %d\n",
            get_remaining_slots(team), zappy->game.width, zappy->game.height);
        NOTIF_GUIS(it, send_pnw(zappy, it, new));
        zappy->client[ci].type = AI;
    } else
        sdprintf(zappy, CLIENT_S(ci), "ko\n");
}

static void ai_commands(zappy_t *zappy, char *command, int ci)
{
    for (size_t a = 0; ai_cmds[a].name && ai_cmds[a].func; ++a)
        if (!strncmp(command, ai_cmds[a].name, strlen(ai_cmds[a].name))) {
            (*ai_cmds[a].func)(zappy, command, ci);
            return;
        }
    sdprintf(zappy, CLIENT_S(ci), "ko\n");
}

static void gui_commands(zappy_t *zappy, char *command, int ci)
{
    for (size_t a = 0; gui_cmds[a].name && gui_cmds[a].func; ++a)
        if (!strncmp(command, gui_cmds[a].name, strlen(gui_cmds[a].name))) {
            (*gui_cmds[a].func)(zappy, command, ci);
            return;
        }
    sdprintf(zappy, CLIENT_S(ci), "suc\n");
}

static void unknown_commands(zappy_t *zappy, char *command, int ci)
{
    player_t *p = NULL;

    if (!strcmp(command, "GRAPHIC")) {
        zappy->client[ci].type = GUI;
        send_msz(zappy, ci);
        send_sgt(zappy, ci);
        send_mct(zappy, ci);
        send_tna(zappy, ci);
        for (int i = -1; (p = parse_players(zappy, &i, p)); p = p->next)
            p->client ? send_pnw(zappy, ci, p) : 0;
        send_all_eggs(zappy, ci);
        return;
    }
    for (int a = 0; a < zappy->game.nbrTeams; ++a) {
        if (!strcmp(command, zappy->game.teams[a].name)) {
            assign_to_player(zappy, ci, &zappy->game.teams[a]);
            return;
        }
    }
    sdprintf(zappy, CLIENT_S(ci), "ko\n");
}

void switch_commands(zappy_t *zappy, char *command, int ci)
{
    DEBUG_PRINT("com: %s\n", command);
    switch (zappy->client[ci].type) {
        case AI:
            ai_commands(zappy, command, ci);
            break;
        case GUI:
            gui_commands(zappy, command, ci);
            break;
        case UNKNOWN:
            unknown_commands(zappy, command, ci);
            break;
        default:
            break;
    }
}
