/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** parsing.c
*/

#include "../include/server.h"

static bool select_file(int fd)
{
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);
    struct timeval tv = {0, 0};
    select(fd + 1, &readfds, NULL, NULL, &tv);
    return FD_ISSET(fd, &readfds);
}

char *read_file(char *filepath)
{
    struct stat stat_buff;
    int fd = open(filepath, O_RDONLY | O_CREAT, 0664);
    if (fd == -1)
        return NULL;
    if (stat(filepath, &stat_buff) == -1)
        return NULL;
    if (!select_file(fd))
        return NULL;
    char *buff = malloc(sizeof(char) * (stat_buff.st_size + 1));
    if (read(fd, buff, stat_buff.st_size) <= 0)
        return NULL;
    buff[stat_buff.st_size] = 0;
    close(fd);
    return buff;
}
