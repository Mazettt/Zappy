/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** write.c
*/

#include "../include/server.h"

void sdprintf(zappy_t *zappy, int fd, char *format, ...)
{
    va_list args;
    if (!FD_ISSET(fd, &zappy->writefds))
        return;

    va_start(args, format);
    vdprintf(fd, format, args);
    va_end(args);
}

void vsdprintf(zappy_t *zappy, int fd, char *format, va_list args)
{
    if (!FD_ISSET(fd, &zappy->writefds))
        return;
    vdprintf(fd, format, args);
}
