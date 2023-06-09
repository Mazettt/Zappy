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
    int line_pos = 0;
    int col_pos = 0;

    sdprintf(zappy, CLIENT_S(ci), "[%s,", res);
    free(res);
    for (int i = 1; i <= player->level; ++i) {
        line_pos = CAST_POS(player->y - i, HEIGHT);
        for (int j = player->x - i; j <= player->x + i; ++j) {
            col_pos = CAST_POS(j, WIDTH);
            res = get_tile_content(zappy, col_pos, line_pos);
            sdprintf(zappy, CLIENT_S(ci), "%s%s", res,
                (i == player->level && j == player->x + i) ? "" : ",");
            free(res);
        }
    }
    sdprintf(zappy, CLIENT_S(ci), "]\n");
}

void look_east(zappy_t *zappy, int ci)
{
    player_t *player = zappy->client[ci].player;
    char *res = get_tile_content(zappy, player->x, player->y);
    int line_pos = 0;
    int col_pos = 0;

    sdprintf(zappy, CLIENT_S(ci), "[%s,", res);
    free(res);
    for (int i = 1; i <= player->level; ++i) {
        line_pos = CAST_POS(player->x + i, WIDTH);
        for (int j = player->y - i; j <= player->y + i; ++j) {
            col_pos = CAST_POS(j, HEIGHT);
            res = get_tile_content(zappy, line_pos, col_pos);
            sdprintf(zappy, CLIENT_S(ci), "%s%s", res,
                (i == player->level && j == player->y + i) ? "" : ",");
            free(res);
        }
    }
    sdprintf(zappy, CLIENT_S(ci), "]\n");
}

void look_south(zappy_t *zappy, int ci)
{
    player_t *player = zappy->client[ci].player;
    char *res = get_tile_content(zappy, player->x, player->y);
    int line_pos = 0;
    int col_pos = 0;

    sdprintf(zappy, CLIENT_S(ci), "[%s,", res);
    free(res);
    for (int i = 1; i <= player->level; ++i) {
        line_pos = CAST_POS(player->y + i, HEIGHT);
        for (int j = player->x + i; j >= player->x - i; --j) {
            col_pos = CAST_POS(j, WIDTH);
            res = get_tile_content(zappy, col_pos, line_pos);
            sdprintf(zappy, CLIENT_S(ci), "%s%s", res,
                (i == player->level && j == player->x - i) ? "" : ",");
            free(res);
        }
    }
    sdprintf(zappy, CLIENT_S(ci), "]\n");
}

void look_west(zappy_t *zappy, int ci)
{
    player_t *player = zappy->client[ci].player;
    char *res = get_tile_content(zappy, player->x, player->y);
    int line_pos = 0;
    int col_pos = 0;

    sdprintf(zappy, CLIENT_S(ci), "[%s,", res);
    free(res);
    for (int i = 1; i <= player->level; ++i) {
        line_pos = CAST_POS(player->x - i, WIDTH);
        for (int j = player->y + i; j >= player->y - i; --j) {
            col_pos = CAST_POS(j, HEIGHT);
            res = get_tile_content(zappy, line_pos, col_pos);
            sdprintf(zappy, CLIENT_S(ci), "%s%s", res,
                (i == player->level && j == player->y - i) ? "" : ",");
            free(res);
        }
    }
    sdprintf(zappy, CLIENT_S(ci), "]\n");
}
