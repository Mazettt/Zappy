/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** take.c
*/

#include "../../../include/server.h"

static void take(zappy_t *zappy, char *command, int ci)
{
    player_t *player = zappy->client[ci].player;
    char **args = my_str_to_word_array(command, SEPARATOR);
    Item item = get_item(args[1]);
    if (item == NBR_ITEMS) {
        sdprintf(zappy, client_socket(ci), "ko\n");
        return;
    }
    int *resource = &zappy->game.map[player->x][player->y][item];
    if (*resource) {
        player->inventory[item] += 1;
        *resource -= 1;
        sdprintf(zappy, client_socket(ci), "ok\n");
        notif_guis(send_pgt(zappy, notif_it, player, item));
    } else
        sdprintf(zappy, client_socket(ci), "ko\n");
    free_word_array(args);
}

void cmd_take(zappy_t *zappy, char *command, int ci)
{
    (void)command;
    zappy->game.actions = add_action(zappy->game.actions, time_limit(7), strdup(command), ci, take);
}
