/*
** EPITECH PROJECT, 2021
** B-CPE-100-MLH-1-1-cpoolday09-martin.d-herouville
** File description:
** my.h
*/

#ifndef UTILS_H
    #define UTILS_H

    #include <stdlib.h>
    #include <stdio.h>
    #include <stddef.h>
    #include <unistd.h>
    #include <string.h>
    #include <stdbool.h>
    #define RESET "\033[0m"
    #define BLACK "\033[0;30m"
    #define RED "\033[0;31m"
    #define GREEN "\033[0;32m"
    #define YELLOW "\033[0;33m"
    #define BLUE "\033[0;34m"
    #define PURPLE "\033[0;35m"
    #define CYAN "\033[0;36m"
    #define WHITE "\033[0;37m"
    #define BOLD_BLACK "\033[1;30m"
    #define BOLD_RED "\033[1;31m"
    #define BOLD_GREEN "\033[1;32m"
    #define BOLD_YELLOW "\033[1;33m"
    #define BOLD_BLUE "\033[1;34m"
    #define BOLD_PURPLE "\033[1;35m"
    #define BOLD_CYAN "\033[1;36m"
    #define BOLD_WHITE "\033[1;37m"

typedef struct {
    int i;
    int i_a;
    int j_a;
    int nbr_words;
    int nbr_letters;
    bool q;
    char **new_arr;
} infos_t;

#endif
