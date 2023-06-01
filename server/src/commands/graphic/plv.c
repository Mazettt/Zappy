/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** plv.c
*/

#include "../../../include/server.h"

void send_plv(zappy_t *zappy, int ci, player_t *player)
{
    sdprintf(zappy, client_socket(ci), "plv %d %d\n",
        player->id,
        player->level
    );
}

void cmd_plv(zappy_t *zappy, char *command, int ci)
{
    char **arr = my_str_to_word_array(command, SEPARATOR);
    int id = atoi(arr[1]);
    player_t *playerBuff = NULL;
    for (int i = 0, j = 0; (playerBuff = parse_players(zappy, &i, &j));) {
        if (playerBuff->client && playerBuff->id == id) {
            send_plv(zappy, ci, playerBuff);
            free_word_array(arr);
            return;
        }
    }
    sdprintf(zappy, client_socket(ci), "ko\n");
    free_word_array(arr);
}
