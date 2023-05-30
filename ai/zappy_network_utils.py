import sys
import socket
import select
import time
import random
import tensorflow as tf
import numpy as np
import math
import os
import zappy_parsing as zp

def con_to_server(args):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((args["machine"], args["port"]))
    zp.print_log("Connected to {} on port {}".format(args["machine"], args["port"]))
    return sock

def send_to_server(sock, message):
    if message[-1] != "\n":
        message += "\n"
    sock.send(message.encode())

def recv_from_server(sock):
    while True:
        response = sock.recv(4096).decode()
        if response != "":
            break
    return response

def multiple_recv_from_server(sock, timeout):
    response = ""
    start_time = time.time()
    while True:
        if time.time() - start_time > timeout:
            break
        response += sock.recv(4096).decode()
        if response != "":
            break
    return response

def get_player_infos(sock, args):
    zp.print_log("Initializing player...")
    team_cmd = args["team"] + "\n"
    send_to_server(sock, team_cmd)
    print(zp.print_log(recv_from_server(sock)))