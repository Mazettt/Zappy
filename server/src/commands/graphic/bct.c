/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** bct.c
*/

#include "../../../include/server.h"

void send_bct(zappy_t *zappy, int ci, int x, int y)
{
    x = CAST_POS(x, zappy->game.width);
    y = CAST_POS(y, zappy->game.height);
    sdprintf(zappy, CLIENT_S(ci), "bct %d %d %d %d %d %d %d %d %d\n",
        x, y,
        zappy->game.map[x][y][FOOD],
        zappy->game.map[x][y][LINEMATE],
        zappy->game.map[x][y][DERAUMERE],
        zappy->game.map[x][y][SIBUR],
        zappy->game.map[x][y][MENDIANE],
        zappy->game.map[x][y][PHIRAS],
        zappy->game.map[x][y][THYSTAME]
    );
}

void cmd_bct(zappy_t *zappy, char *command, int ci)
{
    char **arr = my_str_to_word_array(command, SEPARATOR);

    if (word_array_len(arr) != 3 || !is_num(arr[1]) || !is_num(arr[2]))
        return free_word_array(arr), send_sbp(zappy, ci);
    send_bct(zappy, ci, atoi(arr[1]), atoi(arr[2]));
    free_word_array(arr);
}
