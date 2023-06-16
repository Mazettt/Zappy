##
## EPITECH PROJECT, 2023
## B-YEP-400-MLH-4-1-zappy-martin.d-herouville
## File description:
## zappy_POV
##

import zappy_dataStruct as zds
import zappy_commands as zc

def POVmanager(p: zds.Player):
    tmp_vision = zc.look(p.client)
    p.POV.vision = []
    for x in range(0, len(tmp_vision)):
        itemString = ""
        for y in range(0, len(tmp_vision[x])):
            itemString = itemString + tmp_vision[x][y]
        itemString = itemString.translate(str.maketrans('', '', '[]'))
        tmpInv = itemParser(itemString)
        p.POV.vision.append(tmpInv)
    if (len(p.POV.vision) == 0):
        p.POV.vision.append(zds.Tile(0,0,0,0,0,0,0))
        print("POV was empty !\n")

def itemParser(itemString):
    tmpInv = zds.Tile(0, 0, 0, 0, 0, 0, 0)
    itemList = itemString.split(' ')
    for x in range(0, len(itemList)):
        if (itemList[x] == "food"):
            tmpInv.food += 1
        if (itemList[x] == "player"):
            tmpInv.nearbyPlayers += 1
        if (itemList[x] == "linemate"):
            tmpInv.linemates += 1
        if (itemList[x] == "deraumere"):
            tmpInv.deraumeres += 1
        if (itemList[x] == "sibur"):
            tmpInv.siburs += 1
        if (itemList[x] == "mendiane"):
            tmpInv.mendianes += 1
        if (itemList[x] == "phira"):
            tmpInv.phiras += 1
        if (itemList[x] == "thystame"):
            tmpInv.thystames += 1
    return tmpInv

def hasFood(p: zds.Player, tileNBR):
    if (p.POV.vision[tileNBR].food > 0):
        return True
    return False

def lookForFood(p: zds.Player):
    if (hasFood(p, 1)):
        p.remindToTurn = "L"
    if (hasFood(p, 3)):
        p.remindToTurn = "R"

    # maxRange = (p.stats.level**2 + 2 * p.stats.level)
    # for x in range (0, maxRange):
    #     if (zp.hasFood(p, x)):
    #         print("i")