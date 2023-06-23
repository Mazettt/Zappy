/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** cmd_buff.c
*/

#include "../include/server.h"

static int cmd_buff_len(client_t *client)
{
    int i = 0;
    cmd_buff_t *tmp = client->cmdBuff;

    while (tmp) {
        ++i;
        tmp = tmp->next;
    }
    return i;
}

void add_cmd_buff(client_t *client, char *command)
{
    cmd_buff_t *new = NULL;
    cmd_buff_t *tmp = NULL;
    if (client->type != GUI &&
    cmd_buff_len(client) + (client->action.func != NULL) >= 10)
        return;
    if (client->type == GUI && cmd_buff_len(client) >= 100)
        return;
    new = malloc(sizeof(cmd_buff_t));
    if (!new)
        return;
    new->c = strdup(command);
    new->next = NULL;
    tmp = client->cmdBuff;
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
