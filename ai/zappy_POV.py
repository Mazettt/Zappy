##
## EPITECH PROJECT, 2023
## B-YEP-400-MLH-4-1-zappy-martin.d-herouville
## File description:
## zappy_POV
##

import ai.zappy_dataStruct as zds
import ai.zappy_commands as zc

def POVmanager(p: zds.Player):
    tmp_vision = zc.look(p.client.sock)
    p.POV.vision = []
    for x in range(0, len(tmp_vision)):
        itemString = ""
        for y in range(0, len(tmp_vision[x])):
            itemString = itemString + tmp_vision[x][y]
        itemString = itemString.translate(str.maketrans('', '', '[]'))
        tmpInv = itemParser(p, itemString)
        p.POV.vision.append(tmpInv)

def itemParser(p: zds.Player, itemString):
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