/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** cmd_buff.c
*/

#include "../include/server.h"

void add_cmd_buff(client_t *client, char *command)
{
    cmd_buff_t *new = malloc(sizeof(cmd_buff_t));
    new->c = strdup(command);
    new->next = NULL;

    cmd_buff_t *tmp = client->cmdBuff;
    while (tmp && tmp->next)
        tmp = tmp->next;
    new->prev = tmp;
    if (tmp)
        tmp->next = new;
    else
        client->cmdBuff = new;
}

void remove_first_cmd_buff(client_t *client)
{
    cmd_buff_t *tmp = client->cmdBuff;
    if (tmp) {
        client->cmdBuff = tmp->next;
        free(tmp->c);
        free(tmp);
    }
}
