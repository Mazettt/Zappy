/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** utils.c
*/

#include "../include/server.h"

void close_command_socket(zappy_t *zappy, int i)
{
    get_socket_infos(&zappy->client[i].command);
    if (client_socket(i) != 0) {
        close(client_socket(i));
        debug_print("Host disconnected, ip %s, port %d\n",
            inet_ntoa(zappy->client[i].command.sa.sin_addr),
            ntohs(zappy->client[i].command.sa.sin_port));
    }
    client_socket(i) = 0;
    zappy->client[i].command.addrlen = 0;
    memset(&zappy->client[i].command.sa, 0,
        sizeof(zappy->client[i].command.sa));
    if (zappy->client[i].last_command) {
        free(zappy->client[i].last_command);
        zappy->client[i].last_command = NULL;
    }
    zappy->client[i].type = UNKNOWN;
    zappy->client[i].passiveMode = false;
}

void free_word_array(char **arr)
{
    for (size_t i = 0; arr[i]; ++i)
        free(arr[i]);
    free(arr);
}

char *get_new_uuid(void)
{
    uuid_t uuid;
    char *uuid_str = malloc(sizeof(char) * UUID_STR_LEN);
    uuid_generate(uuid);
    uuid_unparse_lower(uuid, uuid_str);
    return uuid_str;
}
