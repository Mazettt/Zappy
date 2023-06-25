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
    #define DEBUG 0
    #define DEBUG_PRINT(format, ...) if (DEBUG) printf(format, __VA_ARGS__);
    #define CLIENT_S(i) zappy->client[i].command.s
    #define TIME(x) ((time_t)((float)(x) / (float)(zappy->game.freq) * 1000000))
    #define CAST_POS(x, max) ((x) < 0 ? (max) + (x) : (x) % (max))
    #define NOTIF_GUIS(it, func) \
        for (; it < MAX_CONNECTIONS; ++it) { \
            if (zappy->client[it].command.s && zappy->client[it].type == GUI) \
                func; \
        }
    #define HEIGHT zappy->game.height
    #define WIDTH zappy->game.width
    #define UNUSED __attribute__((unused))
    #ifndef M_PI
        #define M_PI 3.14159265358979323846
    #endif

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
    #include <math.h>

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

typedef enum DirectionTile {
    SAME,
    FRONT,
    FRONT_LEFT,
    LEFT,
    BACK_LEFT,
    BACK,
    BACK_RIGHT,
    RIGHT,
    FRONT_RIGHT,
} DirectionTile;

typedef enum item_e {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    NBR_ITEMS
} item_t;

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
    struct timeval startTime;
    time_t timeUntilDie;

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
    team_t *winningTeam;
    int ***map;
    struct timeval lastRefill;
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
    int r_max_fd;
    fd_set writefds;
    int w_max_fd;
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

typedef struct {
    int x;
    int y;
} pos_t;

char *my_strcat(char *dest , char const *src);
bool is_num(char *str);
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

// args.c
args_t get_args(int ac, char **av);
void print_args(args_t *args);
bool check_args(args_t *args);

// zappy.c
void max_fd(int fd, int *max_fd);
void reset_fd(zappy_t *zappy);
int zappy(args_t args);

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

void cmd_forward(zappy_t *zappy, char *command, int ci);
void cmd_right(zappy_t *zappy, char *command, int ci);
void cmd_left(zappy_t *zappy, char *command, int ci);
void cmd_look(zappy_t *zappy, char *command, int ci);
void look_north(zappy_t *zappy, int ci);
void look_east(zappy_t *zappy, int ci);
void look_south(zappy_t *zappy, int ci);
void look_west(zappy_t *zappy, int ci);
void cmd_inventory(zappy_t *zappy, char *command, int ci);
void cmd_connect_nbr(zappy_t *zappy, char *command, int ci);
void cmd_fork(zappy_t *zappy, char *command, int ci);
void cmd_eject(zappy_t *zappy, char *command, int ci);
void cmd_take(zappy_t *zappy, char *command, int ci);
void cmd_set(zappy_t *zappy, char *command, int ci);
void cmd_broadcast(zappy_t *zappy, char *command, int ci);
void cmd_incantation(zappy_t *zappy, char *command, int ci);

void rankup_players(zappy_t *zappy, player_t *basePlayer);
int nbr_players_incantation(zappy_t *zappy, player_t *basePlayer);
player_t **get_incantation_players(zappy_t *zappy, player_t *basePlayer);

// map size
void send_msz(zappy_t *zappy, int ci);
void cmd_msz(zappy_t *zappy, char *command, int ci);
// time unit request
void send_sgt(zappy_t *zappy, int ci);
void cmd_sgt(zappy_t *zappy, char *command, int ci);
// time unit modification
void send_sst(zappy_t *zappy, int ci);
void cmd_sst(zappy_t *zappy, char *command, int ci);
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
void send_pdr(zappy_t *zappy, int ci, player_t *player, item_t type);
// resource collecting
void send_pgt(zappy_t *zappy, int ci, player_t *player, item_t type);
// player death
void send_pdi(zappy_t *zappy, int ci, player_t *player);
// egg laying by the player
void send_pfk(zappy_t *zappy, int ci, player_t *player);
// an egg was laid by a player
void send_enw(zappy_t *zappy, int ci, player_t *player, egg_t *egg);
// new egg
void send_egg(zappy_t *zappy, int ci, egg_t *egg);
void send_all_eggs(zappy_t *zappy, int ci);
// player connection for an egg
void send_ebo(zappy_t *zappy, int ci, egg_t *egg);
// death of an egg
void send_edi(zappy_t *zappy, int ci, egg_t *egg);
// message from the server
void send_smg(zappy_t *zappy, int ci, char *msg);
// end of the game
void send_seg(zappy_t *zappy, int ci, team_t *winningTeam);
// command parameter
void send_sbp(zappy_t *zappy, int ci);

// parsing
char *read_file(char *filepath);

// player
player_t *parse_players(zappy_t *zappy, int *i, player_t *current);
void kill_player(zappy_t *zappy, player_t *player);
player_t *add_player(zappy_t *zappy, egg_t *egg, client_t *client);
int nbr_players(zappy_t *zappy, int x, int y);
int nbr_players_in_team(team_t *team);

// food
bool check_food(zappy_t *zappy, player_t *player);

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
 * @param zappy struct of the game
 * @param recv_pos position of the reciever
 * @param send_pos position of the sender
 * @param direction direction of the reciever
 * @return int = the cell around the point
 */
int get_direction(zappy_t *zappy, pos_t recv_pos, pos_t send_pos,
    Direction direction);
bool check_win(zappy_t *zappy);
bool init_game(zappy_t *zappy, args_t args);

// item
item_t get_item(char *item);
char *get_item_str(item_t item);

void add_action(client_t *client, time_t duration, char *command,
    void (*func)(zappy_t *, char *, int));
void remove_action(action_t *action);
void exec_action(zappy_t *zappy, action_t *action, int ci);

// resources
bool init_resources(args_t args, game_t *game);
void refill_resources(zappy_t *zappy);
int nbresource(zappy_t *zappy, item_t type);

// cmd buff
void add_cmd_buff(client_t *client, char *command);
void remove_first_cmd_buff(client_t *client);

#endif
