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
#include "../include/utils.h"

bool is_sep(char c, char *sep, bool *quote);
int count_words(char const *str, char *sep, bool *quote);
int count_letters(char const *str, char *sep, bool *quote);
char **set_arr(char **new_arr, int i_a, int j_a);

static bool main_parsing(char const *str, char *sep, infos_t *infos)
{
    if (str[infos->i] == '"')
        infos->q = !infos->q;
    if (infos->i > 0 && is_sep(str[infos->i], sep, &infos->q) &&
    !is_sep(str[infos->i - 1], sep, &infos->q))
        infos->new_arr[infos->i_a][infos->j_a] = '\0';
    if (is_sep(str[infos->i], sep, &infos->q) &&
    !is_sep(str[infos->i + 1], sep, &infos->q) && str[infos->i + 1] != '\0') {
        infos->j_a = 0;
        infos->nbr_letters = count_letters(str + infos->i + 1, sep, &infos->q);
        infos->new_arr[++infos->i_a] = malloc(sizeof(char) *
            (infos->nbr_letters + 1));
        if (!infos->new_arr[infos->i_a])
            return false;
    }
    if (!is_sep(str[infos->i], sep, &infos->q) && str[infos->i] != '\0')
        infos->new_arr[infos->i_a][infos->j_a++] = str[infos->i];
    return true;
}

char **my_str_to_word_array(char const *str, char *sep)
{
    infos_t infos = {.i = 0, .i_a = 0, .j_a = 0, .nbr_words = 0,
    .nbr_letters = 0, .q = false, .new_arr = NULL};

    infos.nbr_words = count_words(str, sep, &infos.q);
    infos.new_arr = malloc(sizeof(char *) * (infos.nbr_words + 1));
    if (!infos.new_arr)
        return NULL;
    for (; is_sep(str[infos.i], sep, &infos.q); ++infos.i)
        infos.q = (str[infos.i] == '"' ? !infos.q : infos.q);
    infos.nbr_letters = count_letters(&str[infos.i], sep, &infos.q);
    infos.new_arr[infos.i_a] = malloc(sizeof(char) * (infos.nbr_letters + 1));
    if (!infos.new_arr[infos.i_a])
        return NULL;
    for (; str[infos.i] != '\0'; ++infos.i)
        if (!main_parsing(str, sep, &infos))
            return NULL;
    infos.new_arr = set_arr(infos.new_arr, infos.i_a, infos.j_a);
    return infos.new_arr;
}
