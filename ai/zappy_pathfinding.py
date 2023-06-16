##
## EPITECH PROJECT, 2023
## B-YEP-400-MLH-4-1-zappy-martin.d-herouville
## File description:
## zappy_pathfinding_food
##

import ai.zappy_dataStruct as zds

def hasFood(p: zds.Player, tileNBR):
    if (p.POV.vision[tileNBR].food > 0):
        return True
    return False

def lookForFood(p: zds.Player):
    if (hasFood(p, 1)):
        p.remindToTurn = "L"
    if (hasFood(p, 3)):
        p.remindToTurn = "R"

def lookForStones(p: zds.Player):
    print("looking for stones")