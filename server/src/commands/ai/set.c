/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** set.c
*/

#include "../../../include/server.h"

static void set(zappy_t *zappy, char *command, int ci)
{
    player_t *player = zappy->client[ci].player;
    char **args = my_str_to_word_array(command, SEPARATOR);
    Item item = get_item(args[1]);
    if (item == NBR_ITEMS) {
        sdprintf(zappy, client_socket(ci), "ko\n");
        return;
    }
    if (player->inventory[item] > 0) {
        player->inventory[item] -= 1;
        zappy->game.resources = add_resource(zappy->game.resources, player->x, player->y, item);
        sdprintf(zappy, client_socket(ci), "ok\n");
    } else
        sdprintf(zappy, client_socket(ci), "ko\n");
    free_word_array(args);
}

void cmd_set(zappy_t *zappy, char *command, int ci)
{
    (void)command;
    zappy->game.actions = add_action(zappy->game.actions, time_limit(7), strdup(command), ci, set);
}
