##
## EPITECH PROJECT, 2023
## B-YEP-400-MLH-4-1-zappy-martin.d-herouville
## File description:
## zappy_elevation
##

import ai.zappy_dataStruct as zds
import ai.zappy_commands as zc
import ai.zappy_inventory as zi
import ai.zappy_network_utils as znu
import ai.zappy_set as zs
import ai.zappy_pathfinding as zpf
import ai.zappy_parsing as zp
import time

def canElevate(p: zds.Player):
    if (p.inventory.linemates + p.POV.vision[0].linemates < p.requirement.linemates):
        return False
    if (p.inventory.deraumeres + p.POV.vision[0].deraumeres < p.requirement.deraumeres):
        return False
    if (p.inventory.siburs + p.POV.vision[0].siburs < p.requirement.siburs):
        return False
    if (p.inventory.mendianes + p.POV.vision[0].mendianes < p.requirement.mendianes):
        return False
    if (p.inventory.phiras + p.POV.vision[0].phiras < p.requirement.phiras):
        return False
    if (p.inventory.thystames + p.POV.vision[0].thystames < p.requirement.thystames):
        return False
    if (zs.setRitual(p) == False):
        return False
    p.AI.elevating = True
    return True

def elevationTry(p: zds.Player):
    zc.broadcast_text(p.client, "Elev {}->Underway\n".format(p.stats.level))
    if (zc.incantation(p.client) == "Elevation underway\n"):
        p.AI.elevating = False
        p.stats.level += 1
        zi.consumeStones(p)
        zi.updatRequirement(p)
    resp = ""
    while (resp[:14] != "Current level:" and resp != "ko\n"):
        resp = znu.multiple_recv_from_server(p.client.sock, 7)
        resp = zp.ElevationMessageParser(p.client, resp)
    if (resp != "ko\n"):
        zc.broadcast_text(p.client, "Elev {}->Done\n".format(p.stats.level - 1))
