/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** look.c
*/

#include "../../../include/server.h"

static void look_north(zappy_t *zappy, int ci)
{
    player_t *player = zappy->client[ci].player;

    char *res = get_tile_content(zappy, player->pos_x, player->pos_y);
    sdprintf(zappy, client_socket(ci), "[%s,", res);
    free(res);
    for (int i = 1; i <= player->level; ++i) {
        int line_pos = cast_pos(player->pos_y + i, HEIGHT);
        for (int j = player->pos_x - i; j <= player->pos_x + i; ++j) {
            int col_pos = cast_pos(j, WIDTH);
            char *res = get_tile_content(zappy, col_pos, line_pos);
            sdprintf(zappy, client_socket(ci), "%s%s", res, (i == player->level && j == player->pos_x + i) ? "" : ",");
            free(res);
        }
    }
    sdprintf(zappy, client_socket(ci), "]\n");
}

static void look_east(zappy_t *zappy, int ci)
{
    player_t *player = zappy->client[ci].player;

    char *res = get_tile_content(zappy, player->pos_x, player->pos_y);
    sdprintf(zappy, client_socket(ci), "[%s,", res);
    free(res);
    for (int i = 1; i <= player->level; ++i) {
        int line_pos = cast_pos(player->pos_x + i, WIDTH);
        for (int j = player->pos_y - i; j <= player->pos_y + i; ++j) {
            int col_pos = cast_pos(j, HEIGHT);
            char *res = get_tile_content(zappy, line_pos, col_pos);
            sdprintf(zappy, client_socket(ci), "%s%s", res, (i == player->level && j == player->pos_y + i) ? "" : ",");
            free(res);
        }
    }
    sdprintf(zappy, client_socket(ci), "]\n");
}

static void look_south(zappy_t *zappy, int ci)
{
    player_t *player = zappy->client[ci].player;

    char *res = get_tile_content(zappy, player->pos_x, player->pos_y);
    sdprintf(zappy, client_socket(ci), "[%s,", res);
    free(res);
    for (int i = 1; i <= player->level; ++i) {
        int line_pos = cast_pos(player->pos_y - i, HEIGHT);
        for (int j = player->pos_x + i; j >= player->pos_x - i; --j) {
            int col_pos = cast_pos(j, WIDTH);
            char *res = get_tile_content(zappy, col_pos, line_pos);
            sdprintf(zappy, client_socket(ci), "%s%s", res, (i == player->level && j == player->pos_x - i) ? "" : ",");
            free(res);
        }
    }
    sdprintf(zappy, client_socket(ci), "]\n");
}

static void look_west(zappy_t *zappy, int ci)
{
    player_t *player = zappy->client[ci].player;

    char *res = get_tile_content(zappy, player->pos_x, player->pos_y);
    sdprintf(zappy, client_socket(ci), "[%s,", res);
    free(res);
    for (int i = 1; i <= player->level; ++i) {
        int line_pos = cast_pos(player->pos_x - i, WIDTH);
        for (int j = player->pos_y + i; j >= player->pos_y - i; --j) {
            int col_pos = cast_pos(j, HEIGHT);
            char *res = get_tile_content(zappy, line_pos, col_pos);
            sdprintf(zappy, client_socket(ci), "%s%s", res, (i == player->level && j == player->pos_y - i) ? "" : ",");
            free(res);
        }
    }
    sdprintf(zappy, client_socket(ci), "]\n");
}

static void look(zappy_t *zappy, int ci)
{
    player_t *player = zappy->client[ci].player;

    switch (player->direction) {
        case NORTH:
            look_north(zappy, ci);
            break;
        case EAST:
            look_east(zappy, ci);
            break;
        case SOUTH:
            look_south(zappy, ci);
            break;
        case WEST:
            look_west(zappy, ci);
            break;
    }
}

void cmd_look(zappy_t *zappy, char *command, int ci)
{
    (void)command;
    zappy->game.actions = add_action(zappy->game.actions, time_limit(7), ci, look);
}
