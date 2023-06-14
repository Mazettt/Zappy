/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** item.c
*/

#include "../include/server.h"

item_t get_item(char *item)
{
    if (!strncmp(item, "food", 4))
        return FOOD;
    if (!strncmp(item, "linemate", 8))
        return LINEMATE;
    if (!strncmp(item, "deraumere", 9))
        return DERAUMERE;
    if (!strncmp(item, "sibur", 5))
        return SIBUR;
    if (!strncmp(item, "mendiane", 8))
        return MENDIANE;
    if (!strncmp(item, "phiras", 6))
        return PHIRAS;
    if (!strncmp(item, "thystame", 8))
        return THYSTAME;
    return NBR_ITEMS;
}

char *get_item_str(item_t item)
{
    if (item == FOOD)
        return "food";
    if (item == LINEMATE)
        return "linemate";
    if (item == DERAUMERE)
        return "deraumere";
    if (item == SIBUR)
        return "sibur";
    if (item == MENDIANE)
        return "mendiane";
    if (item == PHIRAS)
        return "phiras";
    if (item == THYSTAME)
        return "thystame";
    return NULL;
}

int nbresource(zappy_t *zappy, item_t type)
{
    int nbr = 0;

    for (int i = 0; i < zappy->game.width; ++i)
        for (int j = 0; j < zappy->game.height; ++j)
            nbr += zappy->game.map[i][j][type];
    return nbr;
}
