/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** plv.c
*/

#include "../../../include/server.h"

void send_plv(zappy_t *zappy, int ci, player_t *player)
{
    sdprintf(zappy, CLIENT_S(ci), "plv %d %d\n",
        player->id,
        player->level
    );
}

void cmd_plv(zappy_t *zappy, char *command, int ci)
{
    char **arr = my_str_to_word_array(command, SEPARATOR);
    player_t *p = NULL;

    if (word_array_len(arr) != 2 || !is_num(arr[1]))
        return free_word_array(arr), send_sbp(zappy, ci);
    for (int i = -1; (p = parse_players(zappy, &i, p)); p = p->next) {
        if (p->client && p->id == atoi(arr[1])) {
            send_plv(zappy, ci, p);
            free_word_array(arr);
            return;
        }
    }
    send_sbp(zappy, ci);
    free_word_array(arr);
}
