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
    int id = atoi(arr[1]);
    player_t *playerBuff = NULL;
    for (int i = 0, j = 0; (playerBuff = parse_players(zappy, &i, &j));) {
        if (playerBuff->client && playerBuff->id == id) {
            send_ppo(zappy, ci, playerBuff);
            return;
        }
    }
    sdprintf(zappy, client_socket(ci), "ko\n");
}
