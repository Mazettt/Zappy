/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** str_to_word_array_utils.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool is_sep(char c, char *sep, bool *quote)
{
    for (int i = 0; sep[i] != '\0'; ++i)
        if (sep[i] == '"' && *quote && c != '"')
            return false;
    for (int i = 0; sep[i] != '\0'; ++i)
        if (c == sep[i])
            return (true);
    return (false);
}

int count_words(char const *str, char *sep, bool *quote)
{
    int nbr_words = 0;

    for (int i = 0; str[i] != '\0'; ++i)
        if (i > 0 && is_sep(str[i], sep, quote) &&
        !is_sep(str[i + 1], sep, quote)
        && str[i + 1] != '\0')
            ++nbr_words;
    return (nbr_words + 1);
}

int count_letters(char const *str, char *sep, bool *quote)
{
    int i = 0;

    while (!is_sep(str[i], sep, quote) && str[i] != '\0')
        ++i;
    return (i);
}

char **set_arr(char **new_arr, int i_a, int j_a)
{
    new_arr[i_a][j_a] = '\0';
    new_arr[++i_a] = NULL;
    return (new_arr);
}
