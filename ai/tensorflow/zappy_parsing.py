##
## EPITECH PROJECT, 2023
## B-YEP-400-MLH-4-1-zappy-martin.d-herouville
## File description:
## zappy_parsing
##

import sys
import time

def print_usage():
    print("USAGE: ./zappy_ai -p port -n name -h machine\n\tport\tis the port number\n\tname\tis the name of the team\n\tmachine\tis the name of the machine; localhost by default")

def get_args():
    args = {
        "port": 0,
        "name": "",
        "machine": "localhost"
    }
    for i in range(1, len(sys.argv)):
        if sys.argv[i] == "-help" and i == 1:
            print_usage()
            exit(0)
        elif sys.argv[i - 1] == "-p":
            args["port"] = int(sys.argv[i])
        elif sys.argv[i - 1] == "-n":
            args["name"] = sys.argv[i]
        elif sys.argv[i - 1] == "-h":
            args["machine"] = sys.argv[i]
    if args["port"] == 0 or args["name"] == "":
        print("Invalid argument, refer to usage :\n")
        print_usage()
        exit(84)
    print_log("Arguments: {}".format(args))
    return args

def print_log(message):
    time_now = time.strftime("%H:%M:%S", time.localtime())
    print("[{}] {}".format(time_now, message))

def parse_player_infos(infos):
    if (infos == "ko\n"):
        print_log("Error: KO from server")
        exit(84)
    client_num = int(infos.split("\n")[0])
    map_x = int(infos.split("\n")[1].split(" ")[0])
    map_y = int(infos.split("\n")[1].split(" ")[1])
    print_log("Client number: {}".format(client_num))
    print_log("Map size: {}x{}".format(map_x, map_y))
    return client_num, map_x, map_y