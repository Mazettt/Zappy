/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** look_utils.c
*/

#include "../../../include/server.h"

void look_north(zappy_t *zappy, int ci)
{
    player_t *player = zappy->client[ci].player;

    char *res = get_tile_content(zappy, player->x, player->y);
    sdprintf(zappy, client_socket(ci), "[%s,", res);
    free(res);
    for (int i = 1; i <= player->level; ++i) {
        int line_pos = cast_pos(player->y - i, HEIGHT);
        for (int j = player->x - i; j <= player->x + i; ++j) {
            int col_pos = cast_pos(j, WIDTH);
            char *res = get_tile_content(zappy, col_pos, line_pos);
            sdprintf(zappy, client_socket(ci), "%s%s", res,
                (i == player->level && j == player->x + i) ? "" : ",");
            free(res);
        }
    }
    sdprintf(zappy, client_socket(ci), "]\n");
}

void look_east(zappy_t *zappy, int ci)
{
    player_t *player = zappy->client[ci].player;

    char *res = get_tile_content(zappy, player->x, player->y);
    sdprintf(zappy, client_socket(ci), "[%s,", res);
    free(res);
    for (int i = 1; i <= player->level; ++i) {
        int line_pos = cast_pos(player->x + i, WIDTH);
        for (int j = player->y - i; j <= player->y + i; ++j) {
            int col_pos = cast_pos(j, HEIGHT);
            char *res = get_tile_content(zappy, line_pos, col_pos);
            sdprintf(zappy, client_socket(ci), "%s%s", res,
                (i == player->level && j == player->y + i) ? "" : ",");
            free(res);
        }
    }
    sdprintf(zappy, client_socket(ci), "]\n");
}

void look_south(zappy_t *zappy, int ci)
{
    player_t *player = zappy->client[ci].player;

    char *res = get_tile_content(zappy, player->x, player->y);
    sdprintf(zappy, client_socket(ci), "[%s,", res);
    free(res);
    for (int i = 1; i <= player->level; ++i) {
        int line_pos = cast_pos(player->y + i, HEIGHT);
        for (int j = player->x + i; j >= player->x - i; --j) {
            int col_pos = cast_pos(j, WIDTH);
            char *res = get_tile_content(zappy, col_pos, line_pos);
            sdprintf(zappy, client_socket(ci), "%s%s", res,
                (i == player->level && j == player->x - i) ? "" : ",");
            free(res);
        }
    }
    sdprintf(zappy, client_socket(ci), "]\n");
}

void look_west(zappy_t *zappy, int ci)
{
    player_t *player = zappy->client[ci].player;

    char *res = get_tile_content(zappy, player->x, player->y);
    sdprintf(zappy, client_socket(ci), "[%s,", res);
    free(res);
    for (int i = 1; i <= player->level; ++i) {
        int line_pos = cast_pos(player->x - i, WIDTH);
        for (int j = player->y + i; j >= player->y - i; --j) {
            int col_pos = cast_pos(j, HEIGHT);
            char *res = get_tile_content(zappy, line_pos, col_pos);
            sdprintf(zappy, client_socket(ci), "%s%s", res,
                (i == player->level && j == player->y - i) ? "" : ",");
            free(res);
        }
    }
    sdprintf(zappy, client_socket(ci), "]\n");
}
