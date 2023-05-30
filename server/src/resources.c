/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** resources.c
*/

#include "../include/server.h"

resource_t *add_resource(resource_t *resource, int x, int y, Item type)
{
    resource_t *new = malloc(sizeof(resource_t));
    new->x = x;
    new->y = y;
    new->type = type;
    new->prev = NULL;
    new->next = resource;
    if (resource)
        resource->prev = new;
    return new;
}

int nbr_resource(resource_t *resource, int x, int y, Item type)
{
    int count = 0;
    while (resource) {
        if (resource->x == x && resource->y == y && resource->type == type)
            ++count;
        resource = resource->next;
    }
    return count;
}

resource_t *remove_resource(resource_t **head, resource_t *resource)
{
    if (*head == resource)
        *head = resource->next;
    resource_t *prev = resource->prev;
    resource_t *next = resource->next;
    if (prev)
        prev->next = next;
    if (next)
        next->prev = prev;
    free(resource);
    return next;
}
