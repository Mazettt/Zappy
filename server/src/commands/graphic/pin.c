/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** pin.c
*/

#include "../../../include/server.h"

void send_pin(zappy_t *zappy, int ci, player_t *player)
{
    sdprintf(zappy, client_socket(ci), "pin %d %d %d %d %d %d %d %d %d %d\n",
        player->id,
        player->x,
        player->y,
        player->inventory[FOOD],
        player->inventory[LINEMATE],
        player->inventory[DERAUMERE],
        player->inventory[SIBUR],
        player->inventory[MENDIANE],
        player->inventory[PHIRAS],
        player->inventory[THYSTAME]
    );
}

void cmd_pin(zappy_t *zappy, char *command, int ci)
{
    char **arr = my_str_to_word_array(command, SEPARATOR);
    int id = atoi(arr[1]);
    player_t *playerBuff = NULL;
    for (int i = 0, j = 0; (playerBuff = parse_players(zappy, &i, &j));) {
        if (playerBuff->client && playerBuff->id == id) {
            send_pin(zappy, ci, playerBuff);
            free_word_array(arr);
            return;
        }
    }
    sdprintf(zappy, client_socket(ci), "ko\n");
    free_word_array(arr);
}
