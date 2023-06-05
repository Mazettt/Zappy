import sys
import socket
import select
import time
import random
import numpy as np
import math
import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'
import tensorflow as tf
import zappy_parsing as zp
import zappy_network_utils as znu

class Commands:
    FORWARD = {"Forward\n", 7}
    RIGHT = {"Right\n", 7}
    LEFT = {"Left\n", 7}
    LOOK = {"Look\n", 7}
    INVENTORY = {"Inventory\n", 1}
    BROADCAST = {"Broadcast\n", 7}
    CONNECT_NBR = {"Connect_nbr\n", 0}
    FORK = {"Fork\n", 42}
    EJECT = {"Eject\n", 7}
    TAKE = {"Take\n", 7}
    SET = {"Set\n", 7}
    INCANTATION = {"Incantation\n", 300}

def forward(sock: socket.socket):
    znu.send_to_server(sock, "Forward\n")
    resp = znu.multiple_recv_from_server(sock, Commands.FORWARD[1])
    return resp

def right(sock: socket.socket):
    znu.send_to_server(sock, "Right\n")
    resp = znu.multiple_recv_from_server(sock, Commands.RIGHT[1])
    return resp

def left(sock: socket.socket):
    znu.send_to_server(sock, "Left\n")
    resp = znu.multiple_recv_from_server(sock, Commands.LEFT[1])
    return resp

def look(sock: socket.socket, map_x: int, map_y: int):
    znu.send_to_server(sock, "Look\n")
    resp = znu.multiple_recv_from_server(sock, 20)
    map_game = []
    resp = resp[1:-2]
    resp = resp.split(',')
    for line in resp:
        line = line.split(' ')
        map_game.append(line)
    for line in map_game:
        for cell in line:
            if cell == "":
                line.remove(cell)
    return map_game

def inventory(sock: socket.socket):
    znu.send_to_server(sock, "Inventory\n")
    resp = znu.multiple_recv_from_server(sock, 20)
    inventory = {}
    resp = resp.split(',')
    for item in resp:
        item = item.split(' ')
        inventory[item[1]] = int(item[2])
    return inventory

def broadcast_text(sock: socket.socket, text: str):
    znu.send_to_server(sock, "{} {}".format(Commands.BROADCAST[0], text))
    resp = znu.multiple_recv_from_server(sock, Commands.BROADCAST[1])
    return resp

def unused_connect_nbr(sock: socket.socket):
    znu.send_to_server(sock, "Connect_nbr\n")
    resp = znu.multiple_recv_from_server(sock, Commands.CONNECT_NBR[1])
    return resp

def fork(sock: socket.socket):
    znu.send_to_server(sock, "Fork\n")
    resp = znu.multiple_recv_from_server(sock, Commands.FORK[1])
    return resp

def eject(sock: socket.socket):
    znu.send_to_server(sock, "Eject\n")
    resp = znu.multiple_recv_from_server(sock, Commands.EJECT[1])
    return resp

def take(sock: socket.socket, resource: str):
    znu.send_to_server(sock, "{} {}".format(Commands.TAKE[0], resource))
    resp = znu.multiple_recv_from_server(sock, Commands.TAKE[1])
    return resp

def set(sock: socket.socket, resource: str):
    znu.send_to_server(sock, "{} {}".format(Commands.SET[0], resource))
    resp = znu.multiple_recv_from_server(sock, Commands.SET[1])
    return resp

def incantation(sock: socket.socket):
    znu.send_to_server(sock, Commands.INCANTATION[0])
    resp = znu.multiple_recv_from_server(sock, Commands.INCANTATION[1])
    return resp

def view_map(map: list, map_x: int, map_y: int):
    for line in map:
        for cell in line:
            print(cell, end=' ')
        print()