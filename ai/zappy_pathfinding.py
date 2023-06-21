##
## EPITECH PROJECT, 2023
## B-YEP-400-MLH-4-1-zappy-martin.d-herouville
## File description:
## zappy_pathfinding_food
##

import ai.zappy_dataStruct as zds
import ai.zappy_commands as zc
import ai.zappy_inventory as zi
import ai.zappy_elevation as ze
import ai.zappy_POV as zp

def foodAmount(p: zds.Player, tileNBR):
    if (len(p.POV.vision) <= tileNBR):
        return 0
    return p.POV.vision[tileNBR].food

def huntForFood(p: zds.Player):
    if (foodAmount(p, 1) > foodAmount(p, 3)):
        zc.forward(p.client)
        zc.left(p.client)
    elif (foodAmount(p, 3) > 0):
        zc.forward(p.client)
        zc.right(p.client)
    else:
        zc.forward(p.client)

def gatherStones(p: zds.Player):
    print("looking for stones")

def isPlayer(p: zds.Player, tileNBR):
    if (len(p.POV.vision) <= tileNBR):
        return False
    if (tileNBR == 0 and p.POV.vision[tileNBR].nearbyPlayers > 1):
        return True
    elif (tileNBR != 0 and p.POV.vision[tileNBR].nearbyPlayers > 0):
        return True
    else:
        return False

def chasePlayerStraightLine(p: zds.Player):
    if (isPlayer(p, 2)):
        zc.forward(p.client)
    elif (isPlayer(p, 6)):
        zc.forward(p.client)
        zc.forward(p.client)
    elif (isPlayer(p, 12)):
        zc.forward(p.client)
        zc.forward(p.client)
        zc.forward(p.client)
    elif (isPlayer(p, 20)):
        zc.forward(p.client)
        zc.forward(p.client)
        zc.forward(p.client)
        zc.forward(p.client)
    else:
        zc.forward(p.client)
        zc.forward(p.client)
        zc.forward(p.client)
        zc.forward(p.client)
        zc.forward(p.client)

def moveToClosePlayer(p: zds.Player):
    zi.pickupFood(p)
    zp.POVmanager(p)
    if (isPlayer(p, 0)):
        return
    elif (p.AI.directionToGo in [1, 3, 5, 7]):
        chasePlayerStraightLine(p)
    elif (p.AI.directionToGo in [2, 4, 6, 8]):
        if (isPlayer(p, 2)):
            zc.forward(p.client)
        else:
            zc.forward(p.client)
            zc.left(p.client)
            zc.forward(p.client)

def seekPlayer(p: zds.Player):
    if (p.AI.directionToGo == -1):
        p.AI.seekElevatingPlayer -= 1
        print("launching listen\n")
        zc.listen(p)
    if (p.AI.directionToGo == 0):
        p.AI.elevating = True
        while (p.AI.elevating == True):
           ze.elevationTry(p)
        print("I found the guy AND elevated!")
        exit(0)
        return
    if (p.AI.directionToGo == 1):
        zc.forward(p.client)
        moveToClosePlayer(p)
        return
    if (p.AI.directionToGo == 2):
        zc.left(p.client)
        zc.forward(p.client)
        zi.pickupFood(p)
        zc.right(p.client)
        zc.forward(p.client)
        moveToClosePlayer(p)
        return
    if (p.AI.directionToGo == 3):
        zc.left(p.client)
        zc.forward(p.client)
        moveToClosePlayer(p)
        return
    if (p.AI.directionToGo == 4):
        zc.left(p.client)
        zc.left(p.client)
        zc.forward(p.client)
        zi.pickupFood(p)
        zc.right(p.client)
        zc.forward(p.client)
        moveToClosePlayer(p)
        return
    if (p.AI.directionToGo == 5):
        zc.left(p.client)
        zc.left(p.client)
        zc.forward(p.client)
        moveToClosePlayer(p)
        return
    if (p.AI.directionToGo == 6):
        zc.right(p.client)
        zc.forward(p.client)
        zi.pickupFood(p)
        zc.right(p.client)
        zc.forward(p.client)
        moveToClosePlayer(p)
        return
    if (p.AI.directionToGo == 7):
        zc.right(p.client)
        zc.forward(p.client)
        moveToClosePlayer(p)
        return
    if (p.AI.directionToGo == 8):
        zc.forward(p.client)
        zi.pickupFood(p)
        zc.right(p.client)
        zc.forward(p.client)
        moveToClosePlayer(p)
        return

def turnToDirection(p: zds.Player):
    if (p.AI.remindToTurn == "R" and p.AI.remindToTurnDelay == 0):
        zc.right(p.client)
        p.AI.remindToTurn = "No"
    if (p.AI.remindToTurn == "L" and p.AI.remindToTurnDelay == 0):
        zc.left(p.client)
        p.AI.remindToTurn = "No"
    if (p.AI.remindToTurnDelay > 0):
        p.AI.remindToTurnDelay -= 1