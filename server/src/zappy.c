/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** zappy.c
*/

#include "../include/server.h"

static void reset_fd(zappy_t *zappy)
{
    FD_ZERO(&zappy->readfds);FD_ZERO(&zappy->writefds);
    FD_SET(STDOUT_FILENO, &zappy->writefds);
    if (STDOUT_FILENO > zappy->max_fd) zappy->max_fd = STDOUT_FILENO;
    FD_SET(STDERR_FILENO, &zappy->writefds);
    if (STDERR_FILENO > zappy->max_fd) zappy->max_fd = STDERR_FILENO;
    FD_SET(zappy->main.s, &zappy->readfds);
    FD_SET(zappy->main.s, &zappy->writefds);
    if (zappy->main.s > zappy->max_fd) zappy->max_fd = zappy->main.s;

    for (size_t i = 0; i < MAX_CONNECTIONS; ++i) {
        if (client_socket(i) > 0) {
            FD_SET(client_socket(i), &zappy->readfds);
            FD_SET(client_socket(i), &zappy->writefds);
        }
        if (client_socket(i) > zappy->max_fd)
            zappy->max_fd = client_socket(i);
    }
    FD_SET(zappy->fd_sigint, &zappy->readfds);
    if (zappy->fd_sigint > zappy->max_fd) zappy->max_fd = zappy->fd_sigint;
}

static void first_select(zappy_t *zappy)
{
    int maxSd = 0;
    FD_ZERO(&zappy->writefds);
    FD_SET(STDOUT_FILENO, &zappy->writefds);
    if (STDOUT_FILENO > maxSd)
        maxSd = STDOUT_FILENO;
    FD_SET(STDERR_FILENO, &zappy->writefds);
    if (STDERR_FILENO > maxSd)
        maxSd = STDERR_FILENO;
    select(maxSd + 1, NULL, &zappy->writefds, NULL, NULL);
}

static void free_all(zappy_t *zappy)
{
    for (int i = 0; i < zappy->game.nbrTeams; ++i) {
        free(zappy->game.teams[i].name);
        free(zappy->game.teams[i].players);
    }
    while (zappy->game.resources)
        zappy->game.resources = remove_resource(&zappy->game.resources, zappy->game.resources);
    free(zappy->game.teams);
    free(zappy);
}

static void init_resources(args_t args, game_t *game)
{
    for (int i = 0; i < (args.width * args.height * 0.5); ++i)
        game->resources = add_resource(game->resources, rand() % args.width, rand() % args.height, FOOD);
    for (int i = 0; i < (args.width * args.height * 0.3); ++i)
        game->resources = add_resource(game->resources, rand() % args.width, rand() % args.height, LINEMATE);
    for (int i = 0; i < (args.width * args.height * 0.15); ++i)
        game->resources = add_resource(game->resources, rand() % args.width, rand() % args.height, DERAUMERE);
    for (int i = 0; i < (args.width * args.height * 0.1); ++i)
        game->resources = add_resource(game->resources, rand() % args.width, rand() % args.height, SIBUR);
    for (int i = 0; i < (args.width * args.height * 0.1); ++i)
        game->resources = add_resource(game->resources, rand() % args.width, rand() % args.height, MENDIANE);
    for (int i = 0; i < (args.width * args.height * 0.08); ++i)
        game->resources = add_resource(game->resources, rand() % args.width, rand() % args.height, PHIRAS);
    for (int i = 0; i < (args.width * args.height * 0.05); ++i)
        game->resources = add_resource(game->resources, rand() % args.width, rand() % args.height, THYSTAME);
}

static game_t init_game(args_t args)
{
    int nbrTeams = word_array_len(args.teamNames);
    game_t game = {
        .width = args.width,
        .height = args.height,
        .nbrClients = args.clientsNb,
        .freq = args.freq,
        .teams = malloc(sizeof(team_t) * nbrTeams),
        .nbrTeams = nbrTeams,
        .actions = NULL
    };

    for (int i = 0; i < nbrTeams; ++i) {
        game.teams[i].name = strdup(args.teamNames[i]);
        game.teams[i].players = malloc(sizeof(player_t) * args.clientsNb);
        for (int j = 0; j < args.clientsNb; ++j) {
            game.teams[i].players[j].x = rand() % args.width;
            game.teams[i].players[j].y = rand() % args.height;
            game.teams[i].players[j].direction = SOUTH;
            game.teams[i].players[j].level = 1;
            for (int k = 0; k < NBR_ITEMS; ++k)
                game.teams[i].players[j].inventory[k] = 0;
            game.teams[i].players[j].client = NULL;
        }
    }
    init_resources(args, &game);
    return game;
}

void exec_all_actions(zappy_t *zappy)
{
    action_t *tmp = zappy->game.actions;
    while (tmp) {
        if (exec_action(zappy, tmp))
            tmp = remove_action(&zappy->game.actions, tmp);
        else
            tmp = tmp->next;
    }
}

void zappy(args_t args)
{
    zappy_t *zappy = malloc(sizeof(zappy_t));
    // time_t t = time(NULL);
    zappy->game = init_game(args);
    first_select(zappy);
    init_main_socket(zappy, args.port);
    print_map(zappy);
    while (zappy->main.s) {
        zappy->max_fd = 0;
        reset_fd(zappy);
        select(zappy->max_fd + 1, &zappy->readfds,
            &zappy->writefds, NULL, NULL);
        if (FD_ISSET(zappy->fd_sigint, &zappy->readfds))
            break;
        else {
            accept_new_connections(zappy);
            read_connections(zappy);
        }
        exec_all_actions(zappy);
        // if (time(NULL) - t >= 1) {
        //     t = time(NULL);
        //     print_map(zappy);
        // }
    }
    debug_print("\n%s\n", "Quitting...");
    close_all(zappy);
    free_all(zappy);
}
