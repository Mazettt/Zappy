##
## EPITECH PROJECT, 2023
## B-YEP-400-MLH-4-1-zappy-martin.d-herouville
## File description:
## zappy_commands
##

import socket
import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'
import ai.zappy_network_utils as znu
import ai.zappy_inventory as zi
import ai.zappy_dataStruct as zds
import ai.zappy_parsing as zp

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

def listen(p: zds.Player):
    print("1")
    resp = znu.maybeMultiple_recv_from_server(p.client.sock, 5)
    print("2")
    resp = zp.messageParser(p.client, resp, ["ImpossibleToFound\n"])
    print("3")
    zp.readBufferMessage(p)
    print("4")
    return resp

def forward(client: zds.Client):
    znu.send_to_server(client.sock, "Forward\n")
    resp = ""
    while (resp != "ok\n"):
        resp = znu.multiple_recv_from_server(client.sock, 7)
        resp = zp.messageParser(client, resp, ["ok\n"])
    return resp

def right(client: zds.Client):
    znu.send_to_server(client.sock, "Right\n")
    resp = ""
    while (resp != "ok\n"):
        resp = znu.multiple_recv_from_server(client.sock, 7)
        resp = zp.messageParser(client, resp, ["ok\n"])
    return resp

def left(client: zds.Client):
    znu.send_to_server(client.sock, "Left\n")
    resp = ""
    while (resp != "ok\n"):
        resp = znu.multiple_recv_from_server(client.sock, 7)
        resp = zp.messageParser(client, resp, ["ok\n"])
    return resp

def look(client: zds.Client):
    znu.send_to_server(client.sock, "Look\n")
    resp = "NOTFOUND"
    while (resp == "NOTFOUND"):
        resp = znu.multiple_recv_from_server(client.sock, 7)
        resp = zp.lookMessageParser(client, resp)
    return resp

def inventory(client: zds.Client):
    znu.send_to_server(client.sock, "Inventory\n")
    resp = "N"
    while (resp[0] != '['):
        resp = znu.multiple_recv_from_server(client.sock, 20)
        resp = zp.lookMessageParser(client, resp)
    resp = resp.translate(str.maketrans('', '', '[]'))
    return (zi.inventoryParser(resp, client.sock))

def broadcast_text(client: zds.Client, text: str):
    znu.send_to_server(client.sock, "{} {}".format("Broadcast", text))
    resp = ""
    while (resp != "ok\n"):
        resp = znu.multiple_recv_from_server(client.sock, 7)
        resp = zp.messageParser(client, resp, ["ok\n"])
    return resp

def isNumber(value):
    try:
        float(value)
        return True
    except ValueError:
        return False

def unused_connect_nbr(client: zds.Client):
    znu.send_to_server(client.sock, "Connect_nbr\n")
    resp = ""
    while (isNumber(resp) == False):
        resp = znu.multiple_recv_from_server(client.sock, 0)
        resp = zp.NBRmessageParser(client, resp)
    return resp

def fork(client: zds.Client):
    znu.send_to_server(client.sock, "Fork\n")
    resp = ""
    while (resp != "ok\n"):
        resp = znu.multiple_recv_from_server(client.sock, 42)
        resp = zp.messageParser(client, resp, ["ok\n"])
    return resp

def eject(client: zds.Client):
    znu.send_to_server(client.sock, "Eject\n")
    resp = ""
    while (resp != "ok\n" and resp != "ko\n"):
        resp = znu.multiple_recv_from_server(client.sock, 7)
        resp = zp.messageParser(client, resp, ["ok\n", "ko\n"])
    return resp

def take(client: zds.Client, resource: str):
    znu.send_to_server(client.sock, "{} {}".format("Take", resource))
    resp = ""
    while (resp != "ok\n" and resp != "ko\n"):
        resp = znu.multiple_recv_from_server(client.sock, 7)
        resp = zp.messageParser(client, resp, ["ok\n", "ko\n"])
    return resp

def set(client: zds.Client, resource: str):
    znu.send_to_server(client.sock, "{} {}".format("Set", resource))
    resp = ""
    while (resp != "ok\n" and resp != "ko\n"):
        resp = znu.multiple_recv_from_server(client.sock, 7)
        resp = zp.messageParser(client, resp, ["ok\n", "ko\n"])
    return resp

def incantation(client: zds.Client):
    znu.send_to_server(client.sock, "Incantation\n")
    resp = ""
    while (resp != "Elevation underway\n" and resp != "ko\n"):
        resp = znu.multiple_recv_from_server(client.sock, 300)
        resp = zp.messageParser(client, resp, ["Elevation underway\n", "ko\n"])
    return resp

def view_map(map: list, map_x: int, map_y: int):
    for line in map:
        for cell in line:
            print(cell, end=' ')
        print()