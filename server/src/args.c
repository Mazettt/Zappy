/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** args.c
*/

#include "../include/server.h"

static void get_teams(args_t *args, int ac, char **av, int *i)
{
    ++(*i);
    for (int count = 0; *i < ac && av[*i][0] != '-'; ++*i) {
        args->teamNames =
            realloc(args->teamNames, sizeof(char *) * (count + 2));
        if (!args->teamNames)
            exit(84);
        args->teamNames[count] = av[*i];
        args->teamNames[++count] = NULL;
    }
    --(*i);
}

args_t get_args(int ac, char **av)
{
    args_t args = {.port = 4242, .width = 42, .height = 42, .teamNames = NULL,
        .clientsNb = 10, .freq = 100};

    for (int i = 1; i < ac; ++i) {
        if (!strcmp(av[i], "-p") && i + 1 < ac)
            args.port = atoi(av[i + 1]);
        if (!strcmp(av[i], "-x") && i + 1 < ac)
            args.width = atoi(av[i + 1]);
        if (!strcmp(av[i], "-y") && i + 1 < ac)
            args.height = atoi(av[i + 1]);
        if (!strcmp(av[i], "-n"))
            get_teams(&args, ac, av, &i);
        if (!strcmp(av[i], "-c") && i + 1 < ac)
            args.clientsNb = atoi(av[i + 1]);
        if (!strcmp(av[i], "-f") && i + 1 < ac)
            args.freq = atoi(av[i + 1]);
    }
    return args;
}

void print_args(args_t *args)
{
    DEBUG_PRINT("port: %d\n", args->port);
    DEBUG_PRINT("width: %d\n", args->width);
    DEBUG_PRINT("height: %d\n", args->height);
    if (DEBUG)
        printf("names: ");
    for (int i = 0; args->teamNames && args->teamNames[i]; ++i)
        DEBUG_PRINT("%s ", args->teamNames[i]);
    DEBUG_PRINT("\nclientsNb: %d\n", args->clientsNb);
    DEBUG_PRINT("freq: %d\n", args->freq);
}

bool check_args(args_t *args)
{
    if (args->port < 1 || args->port > 65535)
        return false;
    if (args->width < 1 || args->height < 1)
        return false;
    if (args->clientsNb < 1)
        return false;
    if (args->freq < 1)
        return false;
    if (args->teamNames == NULL)
        return false;
    return true;
}
