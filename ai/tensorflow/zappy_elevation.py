##
## EPITECH PROJECT, 2023
## B-YEP-400-MLH-4-1-zappy-martin.d-herouville
## File description:
## zappy_elevation
##

import zappy_dataStruct as zds
import zappy_commands as zc
import zappy_inventory as zi
import zappy_network_utils as znu
import zappy_set as zs
import time

def canElevate(p: zds.Player):
    if (p.inventory.food < p.stats.level * 3):
        return False
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
    zc.broadcast_text(p.client, "Elevating over here!\n")
    p.stats.elevating = True
    return True

def elevationTry(p: zds.Player):
    if (zc.incantation(p.client) == "Elevation underway\n"):
        p.stats.elevating = False
        p.stats.level += 1
        zi.consumeStones(p)
        zi.updatRequirement(p)
    resp = znu.multiple_recv_from_server(p.client.sock, 300)
    while (resp[:14] != "Current level:" and resp != "ko\n"):
        p.client.buffer.append(resp)
        resp = znu.multiple_recv_from_server(p.client.sock, 7)
