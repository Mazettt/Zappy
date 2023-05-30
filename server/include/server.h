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
    #define time_limit(x) (x / zappy->game.freq * 1000000)

    #include "utils.h"
    #include <sys/socket.h>
    #include <sys/select.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <sys/stat.h>
    #include <sys/time.h>
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
struct zappy_s;
typedef struct zappy_s zappy_t;

typedef enum Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST
} Direction;

typedef struct {
    int pos_x;
    int pos_y;
    Direction direction;
    int level;
    client_t *client;
} player_t;

typedef struct {
    char *name;
    player_t *players;
} team_t;

typedef struct action_s {
    struct timeval startTime;
    time_t duration;
    int ci;
    void (*func)(zappy_t *, int);
    struct action_s *prev;
    struct action_s *next;
} action_t;

typedef struct {
    int width;
    int height;
    int nbrClients;
    int freq;
    team_t *teams;
    int nbrTeams;
    action_t *actions;
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

struct zappy_s {
    socket_t main;
    int fd_sigint;
    client_t client[MAX_CONNECTIONS];
    fd_set readfds;
    fd_set writefds;
    int max_fd;
    int port;
    game_t game;
};

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
void close_command_socket(zappy_t *zappy, int ci);
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
void switch_commands(zappy_t *zappy, char *command, int ci);
void cmd_stop(zappy_t *zappy, char *command, int ci);
void cmd_noop(zappy_t *zappy, char *command, int ci);
void cmd_forward(zappy_t *zappy, char *command, int ci);
void cmd_right(zappy_t *zappy, char *command, int ci);
void cmd_left(zappy_t *zappy, char *command, int ci);

// parsing
char *read_file(char *filepath);

// game
bool is_player(zappy_t *zappy, int x, int y);
void print_map(zappy_t *zappy);

/**
 * @brief add an action to be executed after a certain amount of time
 *
 * @param action action linked list
 * @param duration time to wait before executing the action in microseconds
 * @param i client index
 * @param func function to execute
 * @return action_t* = pointer to the new action
 */
action_t *add_action(action_t *action, time_t duration, int ci, void (*func)(zappy_t *, int));
/**
 * @brief execute the action if the time has passed
 *
 * @param zappy zappy struct
 * @param action action to execute
 * @return true if the action has been executed
 * @return false if the action has not been executed
 */
bool exec_action(zappy_t *zappy, action_t *action);
/**
 * @brief remove an action from the action linked list
 *
 * @param head action linked list
 * @param action action to remove
 * @return action_t* = pointer to the next action
 */
action_t *remove_action(action_t **head, action_t *action);

#endif
