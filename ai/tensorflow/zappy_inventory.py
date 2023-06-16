##
## EPITECH PROJECT, 2023
## B-YEP-400-MLH-4-1-zappy-martin.d-herouville
## File description:
## zappy_inventory
##

import zappy_commands as zc
import zappy_dataStruct as zds
import zappy_network_utils as znu

def pickupFood(p: zds.Player):
    if (p.POV.vision[0].food > 0):
        zc.take(p.client, "food\n")
        p.inventory.food += 1
        p.POV.vision[0].food -=1
        pickupFood(p)

def pickupItems(p: zds.Player):
    if (p.POV.vision[0].linemates > 0 and p.inventory.linemates < p.requirement.linemates):
        zc.take(p.client, "linemate\n")
        p.inventory.linemates += 1
        p.POV.vision[0].linemates -=1
        pickupItems(p)
    if (p.POV.vision[0].deraumeres > 0 and p.inventory.deraumeres < p.requirement.deraumeres):
        zc.take(p.client, "deraumere\n")
        p.inventory.deraumeres += 1
        p.POV.vision[0].deraumeres -=1
        pickupItems(p)
    if (p.POV.vision[0].siburs > 0 and p.inventory.siburs < p.requirement.siburs):
        zc.take(p.client, "sibur\n")
        p.inventory.siburs += 1
        p.POV.vision[0].siburs -=1
        pickupItems(p)
    if (p.POV.vision[0].mendianes > 0 and p.inventory.mendianes < p.requirement.mendianes):
        zc.take(p.client, "mendiane\n")
        p.inventory.mendianes += 1
        p.POV.vision[0].mendianes -=1
        pickupItems(p)
    if (p.POV.vision[0].phiras > 0 and p.inventory.phiras < p.requirement.phiras):
        zc.take(p.client, "phiras\n")
        p.inventory.phiras += 1
        p.POV.vision[0].phiras -=1
        pickupItems(p)
    if (p.POV.vision[0].thystames > 0 and p.inventory.thystames < p.requirement.thystames):
        zc.take(p.client, "thystame\n")
        p.inventory.thystames += 1
        p.POV.vision[0].thystames -=1
        pickupItems(p)

def findValue(strWithNBR):
    number = ""
    for char in strWithNBR:
        if char.isdigit():
            number += char
    if number:
        return int(number)
    else:
        return 0

def inventoryParser(strInventory, sock):
    tmpInv = zds.Tile(0, 0, 0, 0, 0, 0, 0)
    itemList = strInventory.split(',')
    tmpInv.food = findValue(itemList[0])
    tmpInv.linemates = findValue(itemList[1])
    tmpInv.deraumeres = findValue(itemList[2])
    tmpInv.siburs = findValue(itemList[3])
    tmpInv.mendianes = findValue(itemList[4])
    tmpInv.phiras = findValue(itemList[5])
    tmpInv.thystames = findValue(itemList[6])
    return tmpInv

def trashStones(p: zds.Player): #Not used yet, might be deleted in the future
    p.inventory.linemates = 0
    p.inventory.deraumeres = 0
    p.inventory.siburs = 0
    p.inventory.mendianes = 0
    p.inventory.phiras = 0
    p.inventory.thystames = 0

def consumeStones(p: zds.Player):
    p.POV.vision[0].linemates -= p.requirement.linemates
    p.POV.vision[0].deraumeres -= p.requirement.deraumeres
    p.POV.vision[0].siburs -= p.requirement.siburs
    p.POV.vision[0].mendianes -= p.requirement.mendianes
    p.POV.vision[0].phiras -= p.requirement.phiras
    p.POV.vision[0].thystames -= p.requirement.thystames

def updatRequirement(p: zds.Player):
    if (p.stats.level == 2):
        p.requirement = zds.Tile(1, 1, 1, 1, 0, 0, 0)
    if (p.stats.level == 3):
        p.requirement = zds.Tile(1, 2, 0, 1, 0, 2, 0)
    if (p.stats.level == 4):
        p.requirement = zds.Tile(3, 1, 1, 2, 0, 1, 0)
    if (p.stats.level == 5):
        p.requirement = zds.Tile(3, 1, 2, 1, 3, 0, 0)
    if (p.stats.level == 6):
        p.requirement = zds.Tile(5, 1, 2, 3, 0, 1, 0)
    if (p.stats.level == 7):
        p.requirement = zds.Tile(5, 2, 2, 2, 2, 2, 1)

def eat(p: zds.Player):
    if (p.inventory.food > 0):
        p.inventory.food -= 1
        return
    else:
        p.stats.isAlive = False