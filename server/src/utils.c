/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** utils.c
*/

#include "../include/server.h"

void close_command_socket(zappy_t *zappy, int ci)
{
    get_socket_infos(&zappy->client[ci].command);
    if (client_socket(ci) != 0) {
        close(client_socket(ci));
        debug_print("Host disconnected, ip %s, port %d\n",
            inet_ntoa(zappy->client[ci].command.sa.sin_addr),
            ntohs(zappy->client[ci].command.sa.sin_port));
    }
    client_socket(ci) = 0;
    zappy->client[ci].command.addrlen = 0;
    memset(&zappy->client[ci].command.sa, 0,
        sizeof(zappy->client[ci].command.sa));
    if (zappy->client[ci].last_command) {
        free(zappy->client[ci].last_command);
        zappy->client[ci].last_command = NULL;
    }
    zappy->client[ci].type = UNKNOWN;
    zappy->client[ci].team = NULL;
    zappy->client[ci].player = NULL;
    zappy->client[ci].passiveMode = false;
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
    for (; arr[len]; ++len);
    return len;
}

int get_remaining_slots(team_t *team)
{
    int slots = 0;
    for (int j = 0; j < team->nbrClients; ++j) {
        if (team->players[j].client == NULL)
            ++slots;
    }
    return slots;
}
