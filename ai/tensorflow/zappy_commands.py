##
## EPITECH PROJECT, 2023
## B-YEP-400-MLH-4-1-zappy-martin.d-herouville
## File description:
## zappy_commands
##

import socket
import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'
import zappy_network_utils as znu
import zappy_inventory as zi
import zappy_dataStruct as zds

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

def forward(client: zds.Client):
    znu.send_to_server(client.sock, "Forward\n")
    resp = znu.multiple_recv_from_server(client.sock, 7)
    while (resp != "ok\n"):
        client.buffer.append(resp)
        resp = znu.multiple_recv_from_server(client.sock, 7)
    return resp

def right(client: zds.Client):
    znu.send_to_server(client.sock, "Right\n")
    resp = znu.multiple_recv_from_server(client.sock, 7)
    while (resp != "ok\n"):
        client.buffer.append(resp)
        resp = znu.multiple_recv_from_server(client.sock, 7)
    return resp

def left(client: zds.Client):
    znu.send_to_server(client.sock, "Left\n")
    resp = znu.multiple_recv_from_server(client.sock, 7)
    while (resp != "ok\n"):
        client.buffer.append(resp)
        resp = znu.multiple_recv_from_server(client.sock, 7)
    return resp

def look(client: zds.Client):
    znu.send_to_server(client.sock, "Look\n")
    resp = znu.multiple_recv_from_server(client.sock, 200)
    while (resp[0] != '['):
        client.buffer.append(resp)
        resp = znu.multiple_recv_from_server(client.sock, 200)
    res_resp = [[]]
    resp = resp[1:]
    resp = resp.split(',')
    for i in range(0, len(resp)):
        if resp[i] == "]":
            break
        if i % 2 == 0:
            res_resp.append([])
        res_resp[-1].append(resp[i])
    for i in range(0, len(res_resp)):
        for j in range(0, len(res_resp[i])):
            res_resp[i][j] = res_resp[i][j].replace("\n", "")
            res_resp[i][j] = res_resp[i][j].replace("]", "")
    full_resp = []
    for i in range(0, len(res_resp)):
        for j in range(0, len(res_resp[i])):
            full_resp.append(res_resp[i][j])
    return full_resp


def inventory(client: zds.Client):
    znu.send_to_server(client.sock, "Inventory\n")
    resp = znu.multiple_recv_from_server(client.sock, 20)
    while (resp[0] != '['):
        client.buffer.append(resp)
        resp = znu.multiple_recv_from_server(client.sock, 20)
    resp = resp.translate(str.maketrans('', '', '[]'))
    return (zi.inventoryParser(resp, client.sock))

def broadcast_text(client: zds.Client, text: str):
    znu.send_to_server(client.sock, "{} {}".format("Broadcast", text))
    resp = znu.multiple_recv_from_server(client.sock, 7)
    while (resp != "ok\n"):
        client.buffer.append(resp)
        resp = znu.multiple_recv_from_server(client.sock, 7)
    return resp

def isNumber(value):
    try:
        float(value)
        return True
    except ValueError:
        return False

def unused_connect_nbr(client: zds.Client):
    znu.send_to_server(client.sock, "Connect_nbr\n")
    resp = znu.multiple_recv_from_server(client.sock,0)
    while (isNumber(resp) == False):
        client.buffer.append(resp)
        resp = znu.multiple_recv_from_server(client.sock, 0)
    return resp

def fork(client: zds.Client):
    znu.send_to_server(client.sock, "Fork\n")
    resp = znu.multiple_recv_from_server(client.sock, 42)
    while (resp != "ok\n"):
        client.buffer.append(resp)
        resp = znu.multiple_recv_from_server(client.sock, 42)
    return resp

def eject(client: zds.Client):
    znu.send_to_server(client.sock, "Eject\n")
    resp = znu.multiple_recv_from_server(client.sock, 7)
    while (resp != "ok\n" and resp != "ko\n"):
        client.buffer.append(resp)
        resp = znu.multiple_recv_from_server(client.sock, 7)
    return resp

def take(client: zds.Client, resource: str):
    znu.send_to_server(client.sock, "{} {}".format("Take", resource))
    resp = znu.multiple_recv_from_server(client.sock, 7)
    while (resp != "ok\n" and resp != "ko\n"):
        client.buffer.append(resp)
        resp = znu.multiple_recv_from_server(client.sock, 7)
    return resp

def set(client: zds.Client, resource: str):
    znu.send_to_server(client.sock, "{} {}".format("Set", resource))
    resp = znu.multiple_recv_from_server(client.sock, 7)
    while (resp != "ok\n" and resp != "ko\n"):
        client.buffer.append(resp)
        resp = znu.multiple_recv_from_server(client.sock, 7)
    return resp

def incantation(client: zds.Client):
    znu.send_to_server(client.sock, "Incantation\n")
    resp = znu.multiple_recv_from_server(client.sock, 300)
    while (resp != "Elevation underway\n" and resp != "ko\n"):
        client.buffer.append(resp)
        resp = znu.multiple_recv_from_server(client.sock, 300)
    return resp

def view_map(map: list, map_x: int, map_y: int):
    for line in map:
        for cell in line:
            print(cell, end=' ')
        print()