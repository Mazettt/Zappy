/*
** EPITECH PROJECT, 2021
** project
** File description:
** main.c
*/

#include "../include/server.h"

static void args_help(void)
{
    printf("USAGE: ./zappy_server -p port -x width -y height \
-n name1 name2 ... -c clientsNb -f freq\n");
    printf("\tport\t\tis the port number\n");
    printf("\twidth\t\tis the width of the world\n");
    printf("\theight\t\tis the height of the world\n");
    printf("\tnameX\t\tis the name of the team X\n");
    printf("\tclientsNb\tis the number of authorized clients per team\n");
    printf("\tfreq\t\tis the reciprocal of time unit for execution of \
actions\n");
}

int main(int ac, char **av)
{
    args_t args;
    int ret = 0;

    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
        perror("signal");
        return 84;
    }
    srand(time(NULL));
    if (ac == 2 && (!strcmp(av[1], "-help") || !strcmp(av[1], "-h") ||
    !strcmp(av[1], "--help"))) {
        args_help();
        return 0;
    }
    args = get_args(ac, av);
    if (!check_args(&args))
        return 84;
    print_args(&args);
    ret = zappy(args);
    free(args.teamNames);
    return ret;
}
