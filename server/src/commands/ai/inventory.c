/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** inventory.c
*/

#include "../../../include/server.h"

static void inventory(zappy_t *zappy, char *command, int ci)
{
    (void)command;
    player_t *player = zappy->client[ci].player;

    sdprintf(zappy, client_socket(ci), "[%s %d, %s %d, %s %d, %s %d, %s %d, %s %d, %s %d]\n",
        get_item_str(FOOD), player->inventory[FOOD],
        get_item_str(LINEMATE), player->inventory[LINEMATE],
        get_item_str(DERAUMERE), player->inventory[DERAUMERE],
        get_item_str(SIBUR), player->inventory[SIBUR],
        get_item_str(MENDIANE), player->inventory[MENDIANE],
        get_item_str(PHIRAS), player->inventory[PHIRAS],
        get_item_str(THYSTAME), player->inventory[THYSTAME]
    );
}

void cmd_inventory(zappy_t *zappy, char *command, int ci)
{
    (void)command;
    zappy->game.actions = add_action(zappy->game.actions, time_limit(1), strdup(command), ci, inventory);
}
