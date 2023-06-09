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
    item_t item;
    int it = 0;

    if (!args || !args[0] || !args[1])
        return sdprintf(zappy, CLIENT_S(ci), "ko\n");
    item = get_item(args[1]);
    if (item == NBR_ITEMS)
        return sdprintf(zappy, CLIENT_S(ci), "ko\n");
    if (player->inventory[item] > 0) {
        player->inventory[item] -= 1;
        zappy->game.map[player->x][player->y][item] += 1;
        sdprintf(zappy, CLIENT_S(ci), "ok\n");
        NOTIF_GUIS(it, send_pdr(zappy, it, player, item));
    } else
        sdprintf(zappy, CLIENT_S(ci), "ko\n");
    free_word_array(args);
}

void cmd_set(zappy_t *zappy, char *command, int ci)
{
    add_action(&zappy->client[ci], TIME(7), command, set);
}
