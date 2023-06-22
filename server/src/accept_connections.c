/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** accept_connections.c
*/

#include "../include/server.h"

static bool add_socket_to_index(zappy_t *zappy, int new_s, int i)
{
    struct timeval tv = {0, 0};

    zappy->client[i].command.s = new_s;
    zappy->client[i].command.sa = zappy->main.sa;
    zappy->client[i].command.addrlen = zappy->main.addrlen;
    reset_fd(zappy);
    if (select(zappy->r_max_fd + 1, &zappy->readfds, NULL, NULL, &tv) == -1 ||
    select(zappy->r_max_fd + 1, NULL, &zappy->writefds, NULL, &tv) == -1) {
        close(zappy->client[i].command.s);
        memset(&zappy->client[i], 0, sizeof(client_t));
        return false;
    }
    return true;
}

static void add_socket_to_array(zappy_t *zappy, int new_s)
{
    for (size_t i = 0; i < MAX_CONNECTIONS; ++i) {
        if (CLIENT_S(i) != 0)
            continue;
        if (!add_socket_to_index(zappy, new_s, i))
            return;
        get_socket_infos(&zappy->client[i].command);
        DEBUG_PRINT("Host connected, ip %s, port %d\n",
            inet_ntoa(zappy->client[i].command.sa.sin_addr),
            ntohs(zappy->client[i].command.sa.sin_port));
        sdprintf(zappy, new_s, "WELCOME\n");
        break;
    }
}

void accept_new_connections(zappy_t *zappy)
{
    int new_s = 0;

    if (FD_ISSET(zappy->main.s, &zappy->readfds)) {
        if ((new_s = accept(zappy->main.s, (struct sockaddr *)&zappy->main.sa,
            (socklen_t *)&zappy->main.addrlen)) < 0)
            return;
        add_socket_to_array(zappy, new_s);
    }
}
