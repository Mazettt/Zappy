##
## EPITECH PROJECT, 2023
## B-YEP-400-MLH-4-1-zappy-martin.d-herouville
## File description:
## zappy_manualAI
##

import zappy_commands as zc
import zappy_dataStruct as zds
import zappy_inventory as zi
import zappy_elevation as ze
import zappy_POV as zp

def move(p: zds.Player):
    zc.forward(p.client)
    if (p.remindToTurn == "R"):
        zc.right(p.client)
        p.remindToTurn = "No"
    if (p.remindToTurn == "L"):
        zc.left(p.client)
        p.remindToTurn = "No"

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
        try:
            zp.lookForFood(p)
        except:
            # print("Pfiew ! I was about to crash whie looking for food!\n")
            continue
        move(p)
