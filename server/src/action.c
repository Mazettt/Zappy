/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** action.c
*/

#include "../include/server.h"

action_t *add_action(action_t *action, time_t duration, int ci, void (*func)(zappy_t *, int))
{
    action_t *new = malloc(sizeof(action_t));
    gettimeofday(&new->startTime, NULL);
    new->duration = duration;
    new->ci = ci;
    new->func = func;
    new->prev = NULL;
    new->next = action;
    if (action)
        action->prev = new;
    return new;
}

bool exec_action(zappy_t *zappy, action_t *action)
{
    struct timeval now;
    gettimeofday(&now, NULL);
    time_t micro = (now.tv_sec - action->startTime.tv_sec) * 1000000 + now.tv_usec - action->startTime.tv_usec;
    if (micro >= action->duration) {
        action->func(zappy, action->ci);
        return true;
    }
    return false;
}

action_t *remove_action(action_t **head, action_t *action)
{
    if (*head == action)
        *head = action->next;
    action_t *prev = action->prev;
    action_t *next = action->next;
    if (prev)
        prev->next = next;
    if (next)
        next->prev = prev;
    free(action);
    return next;
}
