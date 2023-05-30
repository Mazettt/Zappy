/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** inventory.c
*/

#include "../../../include/server.h"

static void inventory(zappy_t *zappy, int ci)
{
    player_t *player = zappy->client[ci].player;

    sdprintf(zappy, client_socket(ci), "[food %d, linemate %d, deraumere %d, sibur %d, mendiane %d, phiras %d, thystame %d]\n",
        player->inventory[FOOD], player->inventory[LINEMATE], player->inventory[DERAUMERE], player->inventory[SIBUR],
        player->inventory[MENDIANE], player->inventory[PHIRAS], player->inventory[THYSTAME]);
}

void cmd_inventory(zappy_t *zappy, char *command, int ci)
{
    (void)command;
    zappy->game.actions = add_action(zappy->game.actions, time_limit(1), ci, inventory);
}
