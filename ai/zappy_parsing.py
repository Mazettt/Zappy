##
## EPITECH PROJECT, 2023
## B-YEP-400-MLH-4-1-zappy-martin.d-herouville
## File description:
## zappy_parsing
##

import sys
import time
import ai.zappy_dataStruct as zds
import re

def readBufferMessage(p: zds.Player):
    p.AI.directionToGo = -1
    # for x in range(len(p.client.buffer)):
    x = len(p.client.buffer) - 1
    while (x > 0):
        print("Parsing buffer message: {}".format(p.client.buffer[x]))
        print("number of elevation message  {}".format(p.client.buffer[x][16]))
        print("MY current level: {}\n".format(p.stats.level))
        if (ord(p.client.buffer[x][16]) == (48 + p.stats.level)):
            if (p.client.buffer[x][19] == "U"):
                p.AI.seekElevatingPlayer = 3
                p.AI.directionToGo = ord(p.client.buffer[x][8]) - 48
                # p.client.buffer.remove(x)
                p.client.buffer = []
                return
            elif (p.client.buffer[x][19] == "D"):
                p.AI.seekElevatingPlayer = 0
                # p.client.buffer.remove(x)
                p.client.buffer = []
                return
        del p.client.buffer[x]
        x -= 1


    # if (len(p.client.buffer) == 0):
    #     return
    # if (ord(p.client.buffer[0][16]) == (48 + p.stats.level)):
    #     p.AI.seekElevatingPlayer = 30
    #     p.AI.directionToGo = p.client.buffer[0][9]
    # if (p.client.buffer[0] == "Elev Done\n"):
    #     p.AI.seekElevatingPlayer = False
    # del p.client.buffer[0]

def messageParser(c: zds.Client, messageGot, awaitedMessageList):
    # print("Message to parse: {}".format(messageGot))
    messageList = messageGot.splitlines(True)#messageGot.split('\n') #re.split(r"(?='\n')", messageGot)
    messageToReturn = "NOTFOUND"
    for x in range (len(messageList)):
        if (messageList[x] == ""):
            continue
        # messageList[x] = messageList[x] + '\n'
        UnexpectedMSG = True
        for y in range (len(awaitedMessageList)):
            if (messageList[x] == awaitedMessageList[y]):
                UnexpectedMSG = False
                messageToReturn = messageList[x]
        if (UnexpectedMSG == True):
            # print("PARSERmessage sent to buffer: {}".format(messageList[x]))
            c.buffer.append(messageList[x])
    return messageToReturn

def lookMessageParser(c: zds.Client, messageGot):
    messageList = messageGot.splitlines(True)#messageGot.split('\n') #re.split(r"(?='\n')", messageGot)
    messageToReturn = "NOTFOUND"
    for x in range (0, len(messageList)):
        if (messageList[x] == ""):
            continue
        # messageList[x] = messageList[x] + '\n'
        if (messageList[x][0] != '['):
            # print("LOOKPARSERmessage sent to buffer: {}".format(messageList[x]))
            c.buffer.append(messageList[x])
        else:
            messageToReturn = messageList[x]
    return messageToReturn

def NBRmessageParser(c: zds.Client, messageGot):
    messageList = messageGot.splitlines(True)#messageGot.split('\n') #re.split(r"(?='\n')", messageGot)
    messageToReturn = "NOTFOUND"
    for x in range (0, len(messageList)):
        if (messageList[x] == ""):
            continue
        # messageList[x] = messageList[x] + '\n'
        if (messageList[:-1]).isdigit():
            messageToReturn = messageList[:-1]
        else:
            c.buffer.append(messageList[x])
    return messageToReturn

def ElevationMessageParser(c: zds.Client, messageGot):
    messageList = messageGot.splitlines(True)#messageGot.split('\n') #re.split(r"(?='\n')", messageGot)
    messageToReturn = "NOTFOUND"
    for x in range (0, len(messageList)):
        if (messageList[x] == ""):
            continue
        # messageList[x] = messageList[x] + '\n'
        if (messageList[x][:14] != "Current level:" and messageList[x] != "ko\n"):
            # print("LOOKPARSERmessage sent to buffer: {}\n".format(messageList[x]))
            c.buffer.append(messageList[x])
        else:
            messageToReturn = messageList[x]
    return messageToReturn

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