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
    if (!args || !args[0] || !args[1]) {
        sdprintf(zappy, client_socket(ci), "ko\n");
        return;
    }
    item_t item = get_item(args[1]);
    if (item == NBR_ITEMS) {
        sdprintf(zappy, client_socket(ci), "ko\n");
        return;
    }
    int *resource = &zappy->game.map[player->x][player->y][item];
    if (*resource) {
        player->inventory[item] += 1;
        *resource -= 1;
        sdprintf(zappy, client_socket(ci), "ok\n");
        int it = 0;
        notif_guis(it, send_pgt(zappy, it, player, item));
    } else
        sdprintf(zappy, client_socket(ci), "ko\n");
    free_word_array(args);
}

void cmd_take(zappy_t *zappy, char *command, int ci)
{
    add_action(&zappy->client[ci], time_limit(7), command, take);
}
