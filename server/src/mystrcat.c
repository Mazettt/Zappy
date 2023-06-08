/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** mystrcat.c
*/

#include "../include/utils.h"

char *my_strcat(char *dest , char const *src)
{
    int len_tot = (dest ? strlen(dest) : 0) + (src ? strlen(src) : 0) + 1;
    char *new = malloc(sizeof(char) * len_tot);
    int i = 0;

    if (!new)
        return dest;
    for (; dest && dest[i] != '\0'; ++i)
        new[i] = dest[i];
    for (int j = 0; src && src[j] != '\0'; ++i, ++j)
        new[i] = src[j];
    new[i] = '\0';
    return (new);
}

bool is_num(char *str)
{
    for (int i = 0; str[i]; ++i)
        if (str[i] < '0' || str[i] > '9')
            return false;
    return true;
}
