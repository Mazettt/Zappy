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
    sigset_t s;

    memset(&sa_buff, 0, sizeof(sa_buff));
    zappy->port = port;
    for (size_t i = 0; i < MAX_CONNECTIONS; ++i) {
        memset(&zappy->client[i], 0, sizeof(client_t));
        memset(&zappy->client[i].action, 0, sizeof(action_t));
        zappy->client[i].command = init_socket(0, sa_buff);
        zappy->client[i].type = UNKNOWN;
    }
    if (sigemptyset(&s) == -1 || sigaddset(&s, SIGINT) == -1 ||
    sigprocmask(SIG_BLOCK, &s, NULL) == -1) {
        perror("sigemptyset | sigaddset | sigprocmask");
        exit(84);
    }
    if ((zappy->fd_sigint = signalfd(-1, &s, 0)) == -1) {
        perror("signalfd");
        exit(84);
    }
}

void init_main_socket(zappy_t *zappy, int port)
{
    int oui = 1;

    init_zappy(zappy, port);
    zappy->main.s = socket(AF_INET, SOCK_STREAM, 0);
    if (zappy->main.s == -1 || setsockopt(zappy->main.s, SOL_SOCKET,
    SO_REUSEADDR, &oui, sizeof(oui)) == -1) {
        perror("socket | setsockopt");
        exit(84);
    }
    zappy->main.sa.sin_family = AF_INET;
    zappy->main.sa.sin_addr.s_addr = htonl(INADDR_ANY);
    zappy->main.sa.sin_port = htons(zappy->port);
    zappy->main.addrlen = sizeof(zappy->main.sa);
    if (bind(zappy->main.s, (struct sockaddr*)&zappy->main.sa, zappy->main.
    addrlen) == -1 || listen(zappy->main.s, MAX_CONNECTIONS) == -1) {
        perror("bind | listen");
        exit(84);
    }
    printf("Listening on port %d\n", zappy->port);
}
