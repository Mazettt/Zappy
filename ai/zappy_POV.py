##
## EPITECH PROJECT, 2023
## B-YEP-400-MLH-4-1-zappy-martin.d-herouville
## File description:
## zappy_POV
##

import ai.zappy_dataStruct as zds
import ai.zappy_commands as zc

def POVmanager(p: zds.Player):
    visionString = zc.look(p.client)
    p.POV.vision = []
    visionString = visionString.translate(str.maketrans('', '', '[]'))
    visionList = visionString.split(',')
    for x in range(0, len(visionList)):
        tmpInv = itemParser(visionList[x])
        p.POV.vision.append(tmpInv)

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

    # maxRange = (p.stats.level**2 + 2 * p.stats.level)
    # for x in range (0, maxRange):
    #     if (zp.hasFood(p, x)):
    #         print("i")