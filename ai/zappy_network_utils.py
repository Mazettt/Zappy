import sys
import socket
import select
import time
import random
import numpy as np
import math
import os
import ai.zappy_parsing as zp

def con_to_server(machine, port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((machine, port))
    zp.print_log("Connected to {} on port {}".format(machine, port))
    return sock

def send_to_server(sock: socket.socket, message: str):
    zp.print_log("Sending: {}".format(message))
    if message[-1] != '\n':
        message += '\n'
    sock.sendall(message.encode())

def recv_from_server(sock):
    response = sock.recv(4096).decode()
    zp.print_log("Received: {}".format(response))
    if response == "dead\n":
        exit(0)
    return response

def multiple_recv_from_server(sock, timeout):
    response = ""
    start_time = time.time()
    while time.time() - start_time < timeout:
        response += sock.recv(4096).decode()
        if response[-1] == '\n':
            break
    zp.print_log("Received: {}".format(response))
    if response == "dead\n":
        exit(0)
    return response

def get_player_infos(sock, team):
    zp.print_log("Initializing player...")
    time.sleep(2)
    send_to_server(sock, team)
    response = multiple_recv_from_server(sock, 10)
    zp.print_log("Player initialized")
    return response