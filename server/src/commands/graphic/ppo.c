/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** ppo.c
*/

#include "../../../include/server.h"

void send_ppo(zappy_t *zappy, int ci, player_t *player)
{
    sdprintf(zappy, client_socket(ci), "ppo %d %d %d %d\n",
        player->id,
        player->x,
        player->y,
        player->direction + 1
    );
}

void cmd_ppo(zappy_t *zappy, char *command, int ci)
{
    char **arr = my_str_to_word_array(command, SEPARATOR);
    if (word_array_len(arr) != 2 || !is_num(arr[1]))
        return free_word_array(arr), send_sbp(zappy, ci);
    int id = atoi(arr[1]);
    player_t *playerBuff = NULL;
    for (int i = -1; (playerBuff = parse_players(zappy, &i, playerBuff)); playerBuff = playerBuff->next) {
        if (playerBuff->client && playerBuff->id == id) {
            send_ppo(zappy, ci, playerBuff);
            free_word_array(arr);
            return;
        }
    }
    sdprintf(zappy, client_socket(ci), "ko\n");
    free_word_array(arr);
}
