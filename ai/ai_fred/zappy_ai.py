#!/usr/bin/python3
##
## EPITECH PROJECT, 2023
## B-YEP-400-MLH-4-1-zappy-martin.d-herouville
## File description:
## zappy_ai
##

import time
import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'
import ai.zappy_parsing as zp
import ai.zappy_network_utils as znu
import ai.zappy_commands as zc
import ai.zappy_dataStruct as zds
import ai.zappy_manualAI as zma

def find_food(p: zds.Player, map_str: str):
    for line in map_str:
        for cell in line:
            if cell == "food":
                zp.print_log("Found food")
                return

def go_ai(p: zds.Player, map_str: str, map_x: int, map_y: int):
    while True:
        map_str = zc.look(p.client, map_x, map_y)
        find_food(p, map_str)
        time.sleep(1)

def main():
    args = zp.get_args()
    p = zds.Player(args["port"], args["name"], args["machine"])
    p.client.sock = znu.con_to_server(p.client.machine, p.client.port)
    znu.recv_from_server(p.client.sock)
    p_infos = znu.get_player_infos(p.client.sock, p.stats.team)
    zp.print_log("Player: {}".format(p_infos))
    client_num, map_x, map_y = zp.parse_player_infos(p_infos)
    p.stats.playerNB = client_num
    zma.gameLoop(p)

# try:
main()
# except Exception as e:
#     zp.print_log("Error: {}".format(e))
# IA :
# ia verif si y'en a une
# verif buffer sellect
# algo simple ? random ou analyse map ? algo attentif ? algo très complexe ou lib externe ?

# Les IA peuvent s'attaquer entre elles ?
# Jusqu'à quel LVL on peut monter ?