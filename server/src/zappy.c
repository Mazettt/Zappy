/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** zappy.c
*/

#include "../include/server.h"

void max_fd(int fd, int *max_fd)
{
    if (fd > *max_fd)
        *max_fd = fd;
}

void reset_fd(zappy_t *zappy)
{
    zappy->r_max_fd = 0;
    zappy->w_max_fd = 0;
    FD_ZERO(&zappy->readfds);
    FD_ZERO(&zappy->writefds);
    FD_SET(zappy->main.s, &zappy->readfds);
    FD_SET(zappy->main.s, &zappy->writefds);
    max_fd(zappy->main.s, &zappy->r_max_fd);
    max_fd(zappy->main.s, &zappy->w_max_fd);
    for (size_t i = 0; i < MAX_CONNECTIONS; ++i) {
        if (CLIENT_S(i) > 0) {
            FD_SET(CLIENT_S(i), &zappy->readfds);
            FD_SET(CLIENT_S(i), &zappy->writefds);
        }
        max_fd(CLIENT_S(i), &zappy->r_max_fd);
        max_fd(CLIENT_S(i), &zappy->w_max_fd);
    }
    FD_SET(zappy->fd_sigint, &zappy->readfds);
    max_fd(zappy->fd_sigint, &zappy->r_max_fd);
}

static void free_all(zappy_t *zappy)
{
    close_all(zappy);
    for (int i = 0; i < zappy->game.nbrTeams; ++i) {
        free(zappy->game.teams[i].name);
        while (zappy->game.teams[i].players)
            kill_player(zappy, zappy->game.teams[i].players);
        while (zappy->game.teams[i].eggs)
            kill_egg(zappy, zappy->game.teams[i].eggs);
    }
    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < HEIGHT; ++j)
            free(zappy->game.map[i][j]);
        free(zappy->game.map[i]);
    }
    free(zappy->game.map);
    free(zappy->game.teams);
    free(zappy);
}

bool zappy_loop(zappy_t *zappy)
{
    struct timeval tv = {0, 10};

    reset_fd(zappy);
    if (select(zappy->r_max_fd + 1, &zappy->readfds, NULL, NULL, &tv) < 0) {
        perror("select");
        return false;
    }
    if (select(zappy->w_max_fd + 1, NULL, &zappy->writefds, NULL, &tv) < 0) {
        perror("select");
        return false;
    }
    if (FD_ISSET(zappy->fd_sigint, &zappy->readfds))
        return false;
    accept_new_connections(zappy);
    read_connections(zappy);
    refill_resources(zappy);
    return true;
}

int zappy(args_t args)
{
    zappy_t *zappy = malloc(sizeof(zappy_t));

    if (!zappy || !init_game(zappy, args))
        return 84;
    init_main_socket(zappy, args.port);
    while (zappy->main.s)
        if (!zappy_loop(zappy))
            break;
    printf("\n%s\n", "Quitting...");
    free_all(zappy);
    return 0;
}
