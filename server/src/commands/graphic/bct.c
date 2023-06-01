/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** bct.c
*/

#include "../../../include/server.h"

void send_bct(zappy_t *zappy, int ci, int x, int y)
{
    x = cast_pos(x, zappy->game.width);
    y = cast_pos(y, zappy->game.height);
    sdprintf(zappy, client_socket(ci), "bct %d %d %d %d %d %d %d %d %d\n",
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
    send_bct(zappy, ci, atoi(arr[1]), atoi(arr[2]));
    free_word_array(arr);
}
