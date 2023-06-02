/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** connections.c
*/

#include "../include/server.h"

static void add_socket_to_array(zappy_t *zappy, int new_s)
{
    for (size_t i = 0; i < MAX_CONNECTIONS; ++i) {
        if (client_socket(i) == 0) {
            FD_SET(new_s, &zappy->readfds);
            FD_SET(new_s, &zappy->writefds);
            zappy->max_fd = (new_s > zappy->max_fd) ? new_s : zappy->max_fd;
            select(zappy->max_fd + 1, &zappy->readfds, &zappy->writefds,
                NULL, NULL);
            client_socket(i) = new_s;
            zappy->client[i].command.sa = zappy->main.sa;
            zappy->client[i].command.addrlen = zappy->main.addrlen;

            get_socket_infos(&zappy->client[i].command);
            debug_print("Host connected, ip %s, port %d\n",
                inet_ntoa(zappy->client[i].command.sa.sin_addr),
                ntohs(zappy->client[i].command.sa.sin_port));
            sdprintf(zappy, new_s, "WELCOME\n");
            break;
        }
    }
}

void accept_new_connections(zappy_t *zappy)
{
    int new_s = 0;

    if (FD_ISSET(zappy->main.s, &zappy->readfds)) {
        if ((new_s = accept(zappy->main.s, (struct sockaddr *)&zappy->main.sa,
            (socklen_t *)&zappy->main.addrlen)) < 0)
            return;
        add_socket_to_array(zappy, new_s);
    }
}

static void parse_command(zappy_t *zappy, int ci, char *input) {
    char *backup_start = NULL;
    char *start = NULL;
    char *end = NULL;
    start = strdup(input);
    backup_start = start;
    end = (char *)input;
    while ((end = strchr(start, '\n'))){
        char *res = start;
        res[end - start] = 0;
        res = my_strcat(zappy->client[ci].last_command, res);
        add_cmd_buff(&zappy->client[ci], res);
        free(res);
        free(zappy->client[ci].last_command);
        zappy->client[ci].last_command = NULL;
        start = end + 1;
    }
    if (start && *start)
        zappy->client[ci].last_command = my_strcat(zappy->client[ci].last_command, start);
    free(backup_start);
}

static void read_connection(zappy_t *zappy, int ci)
{
    char buff[1024] = {0};

    if (read(client_socket(ci), buff, 1024) == 0)
        close_command_socket(zappy, &zappy->client[ci]);
    else
        parse_command(zappy, ci, buff);
}

void read_connections(zappy_t *zappy)
{
    for (size_t i = 0; i < MAX_CONNECTIONS; ++i)
        if (zappy->client[i].action.func)
            exec_action(zappy, &zappy->client[i].action, i);
        else if (zappy->client[i].cmdBuff) {
            switch_commands(zappy, zappy->client[i].cmdBuff->c, i);
            remove_first_cmd_buff(&zappy->client[i]);
        } else if (FD_ISSET(client_socket(i), &zappy->readfds))
            read_connection(zappy, i);
}
