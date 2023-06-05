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
    #define notif_it it
    #define notif_guis(func) \
        for (int it = 0; it < MAX_CONNECTIONS; ++it) { \
            if (zappy->client[it].command.s && zappy->client[it].type == GUI) \
                func; \
        }
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

typedef struct player_s {
    int id;
    int x;
    int y;
    Direction direction;
    int level;
    int inventory[NBR_ITEMS];
    team_t *team;
    client_t *client;

    struct player_s *prev;
    struct player_s *next;
} player_t;

typedef struct egg_s {
    int id;
    int x;
    int y;
    team_t *team;

    struct egg_s *prev;
    struct egg_s *next;
} egg_t;

struct team_s {
    char *name;
    player_t *players;
    egg_t *eggs;
};

typedef struct action_s {
    struct timeval startTime;
    time_t duration;
    char *command;
    void (*func)(zappy_t *, char *, int);
} action_t;

typedef struct {
    int width;
    int height;
    int freq;
    int playerIdIt;
    int eggIdIt;
    team_t *teams;
    int nbrTeams;
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

typedef struct cmd_buff_s {
    char *c;
    struct cmd_buff_s *prev;
    struct cmd_buff_s *next;
} cmd_buff_t;

struct client_s {
    socket_t command;
    char *last_command;
    cmd_buff_t *cmdBuff;
    ClientType type;
    team_t *team;
    player_t *player;
    bool passiveMode;
    action_t action;
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
void close_command_socket(zappy_t *zappy, client_t *client);
void free_word_array(char **arr);
size_t word_array_len(char **arr);
int get_remaining_slots(team_t *team);
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
// resource dropping
void send_pdr(zappy_t *zappy, int ci, player_t *player, Item type);
// resource collecting
void send_pgt(zappy_t *zappy, int ci, player_t *player, Item type);
// player death
void send_pdi(zappy_t *zappy, int ci, player_t *player);
// egg laying by the player
void send_pfk(zappy_t *zappy, int ci, player_t *player);
// an egg was laid by a player
void send_enw(zappy_t *zappy, int ci, player_t *player, egg_t *egg);

// parsing
char *read_file(char *filepath);

// player
player_t *parse_players(zappy_t *zappy, int *i, player_t *current);
void kill_player(zappy_t *zappy, player_t *player);
player_t *add_player(zappy_t *zappy, egg_t *egg, client_t *client);
int nbr_players(zappy_t *zappy, int x, int y);
int nbr_players_in_team(team_t *team);

// egg
egg_t *add_egg(zappy_t *zappy, team_t *team);
void kill_egg(zappy_t *zappy, egg_t *egg);
player_t *hatch_egg(zappy_t *zappy, egg_t *egg, client_t *client);
int nbr_eggs_in_team(team_t *team);

// game
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

void add_action(client_t *client, time_t duration, char *command, void (*func)(zappy_t *, char *, int));
void remove_action(action_t *action);
void exec_action(zappy_t *zappy, action_t *action, int ci);

// resources
void init_resources(args_t args, game_t *game);

// cmd buff
void add_cmd_buff(client_t *client, char *command);
void remove_first_cmd_buff(client_t *client);

#endif
