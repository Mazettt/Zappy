/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** server.h
*/

#ifndef SERVER_H
    #define SERVER_H

    #define MAX_CONNECTIONS 1024
    #define OTHER_PORT_RANGE 62000
    #define SEPARATOR " \"\t\r\n"
    #define DEBUG 1
    #define debug_print(format, ...)    \
        if (DEBUG) printf(format, __VA_ARGS__);
    #define client_socket(i) zappy->client[i].command.s

    #include "utils.h"
    #include <sys/socket.h>
    #include <sys/select.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <signal.h>
    #include <sys/signalfd.h>
    #include <uuid/uuid.h>
    #include <string.h>
    #include <stdarg.h>

typedef enum ClientType {
    GRAPHIC,
    AI,
    UNKNOWN
} ClientType;

struct client_s;
typedef struct client_s client_t;

typedef struct {
    int pos_x;
    int pos_y;
    int level;
    client_t *client;
} player_t;

typedef struct {
    char *name;
    player_t *players;
} team_t;

typedef struct {
    int width;
    int height;
    int nbrClients;
    int freq;
    team_t *teams;
    int nbrTeams;
} game_t;

typedef struct {
    char *ip;
    int port;
} ip_t;

typedef struct {
    int s;
    struct sockaddr_in sa;
    int addrlen;
} socket_t;

struct client_s {
    socket_t command;
    char *last_command;
    ClientType type;
    team_t *team;
    player_t *player;
    bool passiveMode;
};

typedef struct {
    socket_t main;
    int fd_sigint;
    client_t client[MAX_CONNECTIONS];
    fd_set readfds;
    fd_set writefds;
    int max_fd;
    int port;
    game_t game;
} zappy_t;

typedef struct {
    char *name;
    void (*func)(zappy_t *, char *, int);
} command_t;

typedef struct {
    int port;
    int width;
    int height;
    char **teamNames;
    int clientsNb;
    int freq;
} args_t;

char *my_strcat(char *dest , char const *src);
char *my_itoa(int nb);
char **my_str_to_word_array(char const *str, char *sep);

/**
 * @brief write to a fd checking if the fd is ready to be written
 *
 * @param zappy zappy struct
 * @param fd fd to write to
 * @param format format string
 * @param ... arguments
 */
void sdprintf(zappy_t *zappy, int fd, char *format, ...);
/**
 * @brief write to a fd checking if the fd is ready to be written
 *
 * @param zappy zappy struct
 * @param fd fd to write to
 * @param format format string
 * @param args arguments
 */
void vsdprintf(zappy_t *zappy, int fd, char *format, va_list args);
void close_command_socket(zappy_t *zappy, int i);
void free_word_array(char **arr);
size_t word_array_len(char **arr);
void close_all(zappy_t *zappy);
char *get_new_uuid(void);

// zappy.c
void zappy(args_t args);

// socket.c
void get_socket_infos(socket_t *so);
socket_t init_socket(int s, struct sockaddr_in sa);
socket_t new_data_socket(int port);
void init_main_socket(zappy_t *zappy, int port);

// connections.c
void accept_new_connections(zappy_t *zappy);
void read_connections(zappy_t *zappy);

// commands.c
void switch_commands(zappy_t *zappy, char *command, int i);
void stop(zappy_t *zappy, char *command, int i);
void noop(zappy_t *zappy, char *command, int i);

// parsing
char *read_file(char *filepath);

// game
void print_map(zappy_t *zappy);

#endif
