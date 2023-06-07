/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** socket.c
*/

#include "../include/server.h"

void get_socket_infos(socket_t *so)
{
    getpeername(so->s, (struct sockaddr *)&so->sa, (socklen_t *)&so->addrlen);
}

socket_t init_socket(int s, struct sockaddr_in sa)
{
    socket_t so = {s, sa, sizeof(sa)};
    return so;
}

static void init_zappy(zappy_t *zappy, int port)
{
    struct sockaddr_in sa_buff;
    memset(&sa_buff, 0, sizeof(sa_buff));

    zappy->port = port;
    for (size_t i = 0; i < MAX_CONNECTIONS; ++i) {
        zappy->client[i].command = init_socket(0, sa_buff);
        zappy->client[i].last_command = NULL;
        zappy->client[i].cmdBuff = NULL;
        zappy->client[i].type = UNKNOWN;
        zappy->client[i].team = NULL;
        zappy->client[i].player = NULL;
        zappy->client[i].passiveMode = false;
        memset(&zappy->client[i].action, 0, sizeof(action_t));
    }

    sigset_t s;
    sigemptyset(&s);
    sigaddset(&s, SIGINT);
    sigprocmask(SIG_BLOCK, &s, NULL);
    zappy->fd_sigint = signalfd(-1, &s, 0);
}

void init_main_socket(zappy_t *zappy, int port)
{
    int oui = 1;
    init_zappy(zappy, port);
    zappy->main.s = socket(AF_INET, SOCK_STREAM, 0);
    if (zappy->main.s == -1) {
        perror("socket");exit(84);
    }
    if (setsockopt(zappy->main.s, SOL_SOCKET, SO_REUSEADDR,
    &oui, sizeof(oui))) {
        perror("setsockopt");exit(84);
    }
    zappy->main.sa.sin_family = AF_INET;
    zappy->main.sa.sin_addr.s_addr = htonl(INADDR_ANY);
    zappy->main.sa.sin_port = htons(zappy->port);
    zappy->main.addrlen = sizeof(zappy->main.sa);
    if (bind(zappy->main.s, (struct sockaddr*)&zappy->main.sa,
    zappy->main.addrlen) || listen(zappy->main.s, MAX_CONNECTIONS) < 0) {
        perror("bind | listen");exit(84);
    }
    printf("Listening on port %d\n", zappy->port);
}
