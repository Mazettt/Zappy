##
## EPITECH PROJECT, 2023
## B-YEP-400-MLH-4-1-zappy-martin.d-herouville
## File description:
## zappy_inventory
##

import ai.zappy_commands as zc
import ai.zappy_dataStruct as zds

def pickUpManager(p: zds.Player, z_c: zds.Client):
    if (p.POV.vision[0].food > 0):
        zc.take(z_c, "food\n")
        p.inventory.food += 1
        p.POV.vision[0].food -=1
        pickUpManager(p, z_c)
    if (p.POV.vision[0].linemates > 0 and p.inventory.linemates < p.requirement.linemates):
        zc.take(z_c, "linemate\n")
        p.inventory.linemates += 1
        p.POV.vision[0].linemates -=1
        pickUpManager(p, z_c)
    if (p.POV.vision[0].deraumeres > 0 and p.inventory.deraumeres < p.requirement.deraumeres):
        zc.take(z_c, "deraumere\n")
        p.inventory.deraumeres += 1
        p.POV.vision[0].deraumeres -=1
        pickUpManager(p, z_c)
    if (p.POV.vision[0].siburs > 0 and p.inventory.siburs < p.requirement.siburs):
        zc.take(z_c, "sibur\n")
        p.inventory.siburs += 1
        p.POV.vision[0].siburs -=1
        pickUpManager(p, z_c)
    if (p.POV.vision[0].mendianes > 0 and p.inventory.mendianes < p.requirement.mendianes):
        zc.take(z_c, "mendiane\n")
        p.inventory.mendianes += 1
        p.POV.vision[0].mendianes -=1
        pickUpManager(p, z_c)
    if (p.POV.vision[0].phiras > 0 and p.inventory.phiras < p.requirement.phiras):
        zc.take(z_c, "phiras\n")
        p.inventory.phiras += 1
        p.POV.vision[0].phiras -=1
        pickUpManager(p, z_c)
    if (p.POV.vision[0].thystames > 0 and p.inventory.thystames < p.requirement.thystames):
        zc.take(z_c, "thystame\n")
        p.inventory.thystames += 1
        p.POV.vision[0].thystames -=1
        pickUpManager(p, z_c)

def trashStones(p: zds.Player): #Not used yet, might be deleted in the future
    p.inventory.linemates = 0
    p.inventory.deraumeres = 0
    p.inventory.siburs = 0
    p.inventory.mendianes = 0
    p.inventory.phiras = 0
    p.inventory.thystames = 0

def consumeStones(p: zds.Player):
    p.inventory.linemates -= p.requirement.linemates
    p.inventory.deraumeres -= p.requirement.deraumeres
    p.inventory.siburs -= p.requirement.siburs
    p.inventory.mendianes -= p.requirement.mendianes
    p.inventory.phiras -= p.requirement.phiras
    p.inventory.thystames -= p.requirement.thystames

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