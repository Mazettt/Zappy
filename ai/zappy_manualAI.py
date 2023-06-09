##
## EPITECH PROJECT, 2023
## B-YEP-400-MLH-4-1-zappy-martin.d-herouville
## File description:
## zappy_manualAI
##

import ai.zappy_commands as zc
import ai.zappy_dataStruct as zds
import ai.zappy_inventory as zi
import ai.zappy_elevation as ze
import ai.zappy_POV as zp
import ai.zappy_network_utils as znu
import select

def move(p: zds.Player):
    zc.forward(p.client.sock)
    if (p.remindToTurn == "R"):
        zc.right(p.client.sock)
        p.remindToTurn = "No"
    if (p.remindToTurn == "L"):
        zc.left(p.client.sock)
        p.remindToTurn = "No"

    # maxRange = (p.stats.level**2 + 2 * p.stats.level)
    # for x in range (0, maxRange):
    #     if (zp.hasFood(p, x)):
    #         print("i")

def lookForFood(p: zds.Player):
    if (zp.hasFood(p, 1)):
        p.remindToTurn = "L"
    if (zp.hasFood(p, 3)):
        p.remindToTurn = "R"

def gameLoop(p: zds.Player):
    while True:
        # zc.inventory(p.client.sock) #will be used later to know mount of food left
        #select
        # if ("dead") = close socket -> exit(0)
        zp.POVmanager(p)
        zi.pickUpManager(p, p.client.sock)
        #Put here an "if" later, to know if we have enough food or not
        try:
            lookForFood(p)
        except:
            continue
        move(p)
