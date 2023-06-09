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
    item_t item;
    int it = 0;
    if (!args || !args[0] || !args[1])
        return sdprintf(zappy, client_socket(ci), "ko\n");
    item = get_item(args[1]);
    if (item == NBR_ITEMS)
        return sdprintf(zappy, client_socket(ci), "ko\n");
    if (zappy->game.map[player->x][player->y][item]) {
        player->inventory[item] += 1;
        zappy->game.map[player->x][player->y][item] -= 1;
        sdprintf(zappy, client_socket(ci), "ok\n");
        notif_guis(it, send_pgt(zappy, it, player, item));
    } else
        sdprintf(zappy, client_socket(ci), "ko\n");
    free_word_array(args);
}

void cmd_take(zappy_t *zappy, char *command, int ci)
{
    add_action(&zappy->client[ci], time_limit(7), command, take);
}
