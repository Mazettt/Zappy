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
import ai.zappy_pathfinding as zpf

def move(p: zds.Player):
    zc.forward(p.client)
    if (p.remindToTurn == "R"):
        zc.right(p.client)
        p.remindToTurn = "No"
    if (p.remindToTurn == "L"):
        zc.left(p.client)
        p.remindToTurn = "No"

def printList(list):
    for item in list:
        print(item)
        print("\n")

def gameLoop(p: zds.Player):
    while True:
        #select ?
        zp.POVmanager(p)
        zi.pickupFood(p)
        p.inventory = zc.inventory(p.client)
        if (ze.canElevate(p)):
            while (p.stats.elevating == True):
                ze.elevationTry(p)
        zi.pickupItems(p)
        # try:
        zpf.lookForFood(p)
        # except:
            # print("Pfiew ! I was about to crash whie looking for food!\n")
            # continue
        if (p.POV.vision.__len__() != 4 and (p.POV.vision.__len__()) != 9 and (p.POV.vision.__len__() != 16)): #Debuging in case of error, not to keep for final product
            print("POV size: ---------{}-------------\n".format(p.POV.vision.__len__()))
            print("ERROR: POV SIZE CHANGED\n")
            printList(p.POV.vision)
            exit(84)
        move(p)
