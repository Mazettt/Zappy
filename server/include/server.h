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
    #define cast_pos(x, max) ((x) < 0 ? (max) + (x) : (x) % (max))
    #define HEIGHT zappy->game.height
    #define WIDTH zappy->game.width

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
    GUI,
    AI,
    UNKNOWN
} ClientType;

typedef enum Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST
} Direction;

typedef enum Item {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    NBR_ITEMS
} Item;

struct team_s;
typedef struct team_s team_t;
struct client_s;
typedef struct client_s client_t;
struct zappy_s;
typedef struct zappy_s zappy_t;

typedef struct {
    int base_lvl;
    int nbr_players;
    int items[NBR_ITEMS];
} elev_cond_t;

typedef struct {
    int id;
    int x;
    int y;
    Direction direction;
    int level;
    int inventory[NBR_ITEMS];
    team_t *team;
    client_t *client;
    bool incanting;
} player_t;

struct team_s {
    char *name;
    int nbrClients;
    player_t *players;
};

typedef struct action_s {
    struct timeval startTime;
    time_t duration;
    char *command;
    int ci;
    void (*func)(zappy_t *, char *, int);
    struct action_s *prev;
    struct action_s *next;
} action_t;

typedef struct {
    int width;
    int height;
    int freq;
    int playerIdIt;
    team_t *teams;
    int nbrTeams;
    action_t *actions;
    int ***map;
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
int get_remaining_slots(team_t *team);
void close_all(zappy_t *zappy);
char *get_new_uuid(void);

// zappy.c
void kill_player(player_t *player);
void init_player(game_t *game, player_t *player, team_t *team);
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
void cmd_look(zappy_t *zappy, char *command, int ci);
void cmd_inventory(zappy_t *zappy, char *command, int ci);
void cmd_connect_nbr(zappy_t *zappy, char *command, int ci);
void cmd_fork(zappy_t *zappy, char *command, int ci);
void cmd_eject(zappy_t *zappy, char *command, int ci);
void cmd_take(zappy_t *zappy, char *command, int ci);
void cmd_set(zappy_t *zappy, char *command, int ci);
void cmd_broadcast(zappy_t *zappy, char *command, int ci);
void cmd_incantation(zappy_t *zappy, char *command, int ci);

// map size
void send_msz(zappy_t *zappy, int ci);
void cmd_msz(zappy_t *zappy, char *command, int ci);
// time unit request
void send_sgt(zappy_t *zappy, int ci);
void cmd_sgt(zappy_t *zappy, char *command, int ci);
// tile content
void send_bct(zappy_t *zappy, int ci, int x, int y);
void cmd_bct(zappy_t *zappy, char *command, int ci);
// map content (all tiles)
void send_mct(zappy_t *zappy, int ci);
void cmd_mct(zappy_t *zappy, char *command, int ci);
// team names
void send_tna(zappy_t *zappy, int ci);
void cmd_tna(zappy_t *zappy, char *command, int ci);
// connection of a new player
void send_pnw(zappy_t *zappy, int ci, player_t *player);
// player position
void send_ppo(zappy_t *zappy, int ci, player_t *player);
void cmd_ppo(zappy_t *zappy, char *command, int ci);
// player level
void send_plv(zappy_t *zappy, int ci, player_t *player);
void cmd_plv(zappy_t *zappy, char *command, int ci);
// player inventory
void send_pin(zappy_t *zappy, int ci, player_t *player);
void cmd_pin(zappy_t *zappy, char *command, int ci);
// expulsion
void send_pex(zappy_t *zappy, int ci, player_t *player);
// broadcast
void send_pbc(zappy_t *zappy, int ci, player_t *player, char *message);
// start of incantation
void send_pic(zappy_t *zappy, int ci, player_t **players);
// end of incantation
void send_pie(zappy_t *zappy, int ci, player_t *player, bool result);
// parsing
char *read_file(char *filepath);

// game
int nbr_players(zappy_t *zappy, int x, int y);
player_t *parse_players(zappy_t *zappy, int *i, int *j);
char *get_tile_content(zappy_t *zappy, int x, int y);
/**
 * @brief get the cell around a point where the direction is coming
 *
 * @param x x coordinate of the point to get the direction
 * @param y y coordinate of the point to get the direction
 * @param dx x coordinate of the pointthe direction is coming from
 * @param dy y coordinate of the pointthe direction is coming from
 * @param direction direction of the object
 * @return int = the cell around the point
 */
int get_direction(int x, int y, int dx, int dy, Direction direction);
/**
 * @brief get the item from a string
 *
 * @param item string to get the item from
 * @return Item and NBR_ITEMS if the item is not found
 */
Item get_item(char *item);
/**
 * @brief get the string associated to an item
 *
 * @param item item to get the string from
 * @return char* and NULL if the item is not found
 */
char *get_item_str(Item item);

/**
 * @brief add an action to be executed after a certain amount of time
 *
 * @param action action linked list
 * @param duration time to wait before executing the action in microseconds
 * @param i client index
 * @param func function to execute
 * @return action_t* = pointer to the new action
 */
action_t *add_action(action_t *action, time_t duration, char *command, int ci, void (*func)(zappy_t *, char *, int));
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

// resources
void init_resources(args_t args, game_t *game);

#endif
