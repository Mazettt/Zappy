/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** direction.c
*/

#include "../include/server.h"

static int cast_angle(float angle)
{
    if (angle >= 0 && angle < 45)
        return FRONT_RIGHT;
    if (angle >= 45 && angle < 90)
        return FRONT;
    if (angle >= 90 && angle < 135)
        return FRONT_LEFT;
    if (angle >= 135 && angle < 180)
        return LEFT;
    if (angle >= 180 && angle < 225)
        return BACK_LEFT;
    if (angle >= 225 && angle < 270)
        return BACK;
    if (angle >= 270 && angle < 315)
        return BACK_RIGHT;
    if (angle >= 315 && angle < 360)
        return RIGHT;
    return SAME;
}

static float get_angle(pos_t recv, pos_t send_pos)
{
    float angle = atan2(-(send_pos.y - recv.y), send_pos.x - recv.x) *
        (180 / M_PI) - 22.5;
    if (angle < 0)
        angle += 360;
    return angle;
}

static double calc_distance(pos_t first, pos_t second)
{
    return sqrt(pow(second.x - first.x, 2) + pow(second.y - first.y, 2));
}

static pos_t get_new_recv(pos_t map_size, pos_t recv_pos, pos_t send_pos)
{
    double buffdist = 0;
    double min = -1;
    pos_t buffpos = {0, 0};
    pos_t res = {0, 0};
    const pos_t map_extrems[9] = {
        { -map_size.x, -map_size.y }, { 0, -map_size.y },
        { map_size.x, -map_size.y }, { -map_size.x, 0 }, { 0, 0 },
        { map_size.x, 0 }, { -map_size.x, map_size.y }, { 0, map_size.y },
        { map_size.x, map_size.y }
    };
    for (int i = 0; i < 9; i++) {
        buffpos.x = map_extrems[i].x + recv_pos.x;
        buffpos.y = map_extrems[i].y + recv_pos.y;
        buffdist = calc_distance(send_pos, buffpos);
        if (buffdist <= min || min == -1) {
            min = buffdist;
            res = buffpos;
        }
    }
    return res;
}

int get_direction(zappy_t *zappy, pos_t recv_pos, pos_t send_pos, Direction d)
{
    int res = 0;

    if (recv_pos.x == send_pos.x && recv_pos.y == send_pos.y)
        return SAME;
    res = cast_angle(get_angle(get_new_recv(
        (pos_t){ WIDTH, HEIGHT }, recv_pos, send_pos), send_pos));
    switch (d) {
        case EAST:
            res = (res + 1) % 8 + 1;
            break;
        case SOUTH:
            res = (res + 3) % 8 + 1;
            break;
        case WEST:
            res = (res + 5) % 8 + 1;
            break;
        default:
            break;
    }
    return res;
}
