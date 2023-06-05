/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** utils.c
*/

#include "../include/server.h"

void close_command_socket(zappy_t *zappy, client_t *client)
{
    get_socket_infos(&client->command);
    if (client->command.s != 0) {
        close(client->command.s);
        debug_print("Host disconnected, ip %s, port %d\n",
            inet_ntoa(client->command.sa.sin_addr),
            ntohs(client->command.sa.sin_port));
    }
    if (client->last_command)
        free(client->last_command);
    if (client->player)
        kill_player(zappy, client->player);
    memset(client, 0, sizeof(client_t));
    client->type = UNKNOWN;
}

void free_word_array(char **arr)
{
    for (size_t i = 0; arr[i]; ++i)
        free(arr[i]);
    free(arr);
}

size_t word_array_len(char **arr)
{
    size_t len = 0;
    for (; arr && arr[len]; ++len);
    return len;
}

int get_remaining_slots(team_t *team)
{
    return nbr_eggs_in_team(team);
}
