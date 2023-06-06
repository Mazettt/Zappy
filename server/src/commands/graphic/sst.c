/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** sst.c
*/

#include "../../../include/server.h"

void send_sst(zappy_t *zappy, int ci)
{
    sdprintf(zappy, client_socket(ci), "sst %d\n", zappy->game.freq);
}

void cmd_sst(zappy_t *zappy, char *command, int ci)
{
    char **args = my_str_to_word_array(command, SEPARATOR);
    if (word_array_len(args) != 2 || !is_num(args[1]))
        return free_word_array(args), send_sbp(zappy, ci);
    zappy->game.freq = atoi(args[1]);
    notif_guis(send_sst(zappy, ci));
    free_word_array(args);
}
