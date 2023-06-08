##
## EPITECH PROJECT, 2023
## B-YEP-400-MLH-4-1-zappy-martin.d-herouville
## File description:
## zappy_elevation
##

import ai.zappy_dataStruct as zds
import ai.zappy_commands as zc
import ai.zappy_inventory as zi

def canElevate(p: zds.Player):
    p.stats.elevating = False
    if (p.inventory.linemates < p.requirement.linemates):
        return
    if (p.inventory.deraumeres < p.requirement.deraumeres):
        return
    if (p.inventory.siburs < p.requirement.siburs):
        return
    if (p.inventory.mendianes < p.requirement.mendianes):
        return
    if (p.inventory.phiras < p.requirement.phiras):
        return
    if (p.inventory.thystames < p.requirement.thystames):
        return
    elevationTry(p)

def elevationTry(p: zds.Player):
    p.stats.elevating = True
    if (zc.incantation(p.client.sock) == "Elevation underway\n"):
        p.stats.elevating = False
        p.stats.level += 1
        zi.consumeStones(p)
        zi.updatRequirement(p)