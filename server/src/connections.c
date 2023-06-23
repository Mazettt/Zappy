/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** connections.c
*/

#include "../include/server.h"

static void parse_command(zappy_t *zappy, int ci, char *input)
{
    char *start = strdup(input);
    char *backup_start = start;
    char *end = (char *)input;
    char *res = NULL;
    while ((end = strchr(start, '\n'))){
        res = start;
        res[end - start] = 0;
        res = my_strcat(zappy->client[ci].last_command, res);
        add_cmd_buff(&zappy->client[ci], res);
        free(res);
        free(zappy->client[ci].last_command);
        zappy->client[ci].last_command = NULL;
        start = end + 1;
    }
    if (start && *start) {
        res = my_strcat(zappy->client[ci].last_command, start);
        free(zappy->client[ci].last_command);
        zappy->client[ci].last_command = res;
    }
    free(backup_start);
}

static void read_connection(zappy_t *zappy, int ci)
{
    bool win = check_win(zappy) && zappy->client[ci].type == AI;
    char buff[1024 * 4] = {0};
    ssize_t r = 0;

    if (!win && zappy->client[ci].action.func)
        exec_action(zappy, &zappy->client[ci].action, ci);
    else if (!win && zappy->client[ci].cmdBuff) {
        switch_commands(zappy, zappy->client[ci].cmdBuff->c, ci);
        remove_first_cmd_buff(&zappy->client[ci]);
    }
    if (!FD_ISSET(CLIENT_S(ci), &zappy->readfds))
        return;
    r = read(CLIENT_S(ci), buff, 1024 * 4);
    buff[r] = 0;
    if (r == 0)
        close_command_socket(zappy, &zappy->client[ci]);
    else if (!win)
        parse_command(zappy, ci, buff);
}

void read_connections(zappy_t *zappy)
{
    for (size_t i = 0; i < MAX_CONNECTIONS; ++i) {
        if (!CLIENT_S(i))
            continue;
        if (zappy->client[i].type == AI && !check_win(zappy) &&
        !check_food(zappy, zappy->client[i].player)) {
            sdprintf(zappy, CLIENT_S(i), "dead\n");
            close_command_socket(zappy, &zappy->client[i]);
            continue;
        }
        read_connection(zappy, i);
    }
}
