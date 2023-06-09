/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** action.c
*/

#include "../include/server.h"

void add_action(client_t *client, time_t duration, char *command,
void (*func)(zappy_t *, char *, int))
{
    gettimeofday(&client->action.startTime, NULL);
    client->action.duration = duration;
    client->action.command = strdup(command);
    client->action.func = func;
}

void remove_action(action_t *action)
{
    free(action->command);
    memset(action, 0, sizeof(action_t));
}

void exec_action(zappy_t *zappy, action_t *action, int ci)
{
    struct timeval now;

    gettimeofday(&now, NULL);
    if ((now.tv_sec - action->startTime.tv_sec) * 1000000 +
        (now.tv_usec - action->startTime.tv_usec) >= action->duration) {
        action->func(zappy, action->command, ci);
        remove_action(action);
    }
}
