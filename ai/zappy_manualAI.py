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
import ai.zappy_POV as zpov
import ai.zappy_pathfinding as zpf
import ai.zappy_parsing as zp

def printList(list):
    for item in list:
        print(item)
        print("\n")

def behaviorApply(p: zds.Player):
    if (p.AI.behavior == zds.Behavior.SeekFood):
        zpf.huntForFood(p)
    if (p.AI.behavior == zds.Behavior.SeekStones):
        zpf.huntForFood(p) #To implement a item seeker using remindToTurnDelay = NBR of tiles to go before turning
    if (p.AI.behavior == zds.Behavior.SeekPlayer):
        zpf.seekPlayer(p)
        p.AI.directionToGo = -1
    if (p.AI.behavior == zds.Behavior.Elevate):
        while (p.AI.elevating == True):
           ze.elevationTry(p)

def behaviorSelect(p: zds.Player):
    if (p.AI.behavior == zds.Behavior.SeekFood and p.inventory.food < p.stats.level * 8):
        return
    if (p.inventory.food < p.stats.level * 4):
        p.AI.behavior = zds.Behavior.SeekFood
        return
    else:
        p.AI.behavior = zds.Behavior.SeekStones
    if (p.AI.seekElevatingPlayer > 0):
        p.AI.seekElevatingPlayer -= 1
        p.AI.behavior = zds.Behavior.SeekPlayer
        return
    elif (ze.canElevate(p)):
        p.AI.behavior = zds.Behavior.Elevate

def gameLoop(p: zds.Player):
    while True:
        zpov.POVmanager(p)
        zi.pickupFood(p)
        p.inventory = zc.inventory(p.client)
        zi.pickupItems(p)
        zp.readBufferMessage(p)
        behaviorSelect(p)
        print("------Current behavior: {}------\n".format(p.AI.behavior))
        behaviorApply(p)
