/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** str_to_word_array.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static bool is_sep(char c, char *sep, bool *quote)
{
    for (int i = 0; sep[i] != '\0'; ++i)
        if (sep[i] == '"' && *quote && c != '"')
            return false;
    for (int i = 0; sep[i] != '\0'; ++i)
        if (c == sep[i])
            return (true);
    return (false);
}

static int count_words(char const *str, char *sep, bool *quote)
{
    int nbr_words = 0;

    for (int i = 0; str[i] != '\0'; ++i)
        if (i > 0 && is_sep(str[i], sep, quote) &&
        !is_sep(str[i + 1], sep, quote)
        && str[i + 1] != '\0')
            ++nbr_words;
    if (str[strlen(str) - 1] != ' ')
        ++nbr_words;
    return (nbr_words);
}

static int count_letters(char const *str, char *sep, bool *quote)
{
    int i = 0;

    while (!is_sep(str[i], sep, quote) && str[i] != '\0')
        ++i;
    return (i);
}

static char **set_arr(char **new_arr, int i_a, int j_a)
{
    new_arr[i_a][j_a] = '\0';
    new_arr[++i_a] = NULL;
    return (new_arr);
}

char **my_str_to_word_array(char const *str, char *sep)
{
    int nbr_letters = 0;int i_a = 0;int j_a = 0;int i = 0;
    bool q = false;
    int nbr_words = count_words(str, sep, &q);
    char **new_arr = malloc(sizeof(char *) * (nbr_words + 1));
    for (; is_sep(str[i], sep, &q); ++i)
        q = (str[i] == '"' ? !q : q);
    nbr_letters = count_letters(&str[i], sep, &q);
    new_arr[i_a] = malloc(sizeof(char) * (nbr_letters + 1));
    for (; str[i] != '\0'; ++i) {
        q = (str[i] == '"' ? !q : q);
        if (i > 0 && is_sep(str[i], sep, &q) && !is_sep(str[i - 1], sep, &q))
            new_arr[i_a][j_a] = '\0';
        is_sep(str[i], sep, &q) && !is_sep(str[i + 1], sep, &q) && str[i + 1]
        != '\0' ? j_a = 0, nbr_letters = count_letters(str + i + 1, sep, &q),
        new_arr[++i_a] = malloc(sizeof(char) * (nbr_letters + 1)) : 0;
        !is_sep(str[i], sep, &q) && str[i] != '\0' ? new_arr[i_a][j_a++]
        = str[i] : 0;
    }
    new_arr = set_arr(new_arr, i_a, j_a);
    return (new_arr);
}
