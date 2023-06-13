##
## EPITECH PROJECT, 2023
## B-YEP-400-MLH-4-1-zappy-martin.d-herouville
## File description:
## zappy_set
##

import ai.zappy_commands as zc
import ai.zappy_dataStruct as zds
import ai.zappy_elevation as ze

def setRitual(p: zds.Player):
    if (p.POV.vision[0].linemates < p.requirement.linemates):
        if (zc.set(p.client.sock, "linemate\n") == "ko\n"):
            return False
        p.POV.vision[0].linemates += 1
        p.inventory.linemates -= 1
        return setRitual(p)
    if (p.POV.vision[0].deraumeres < p.requirement.deraumeres):
        if (zc.set(p.client.sock, "deraumere\n") == "ko\n"):
            return False
        p.POV.vision[0].deraumeres += 1
        p.inventory.deraumeres -= 1
        return setRitual(p)
    if (p.POV.vision[0].siburs < p.requirement.siburs):
        if (zc.set(p.client.sock, "siburs\n") == "ko\n"):
            return False
        p.POV.vision[0].siburs += 1
        p.inventory.siburs -= 1
        return setRitual(p)
    if (p.POV.vision[0].mendianes < p.requirement.mendianes):
        if (zc.set(p.client.sock, "mendiane\n") == "ko\n"):
            return False
        p.POV.vision[0].mendianes += 1
        p.inventory.mendianes -= 1
        return setRitual(p)
    if (p.POV.vision[0].phiras < p.requirement.phiras):
        if (zc.set(p.client.sock, "phira\n") == "ko\n"):
            return False
        p.POV.vision[0].phiras += 1
        p.inventory.phiras -= 1
        return setRitual(p)
    if (p.POV.vision[0].thystames < p.requirement.thystames):
        if (zc.set(p.client.sock, "thystame\n") == "ko\n"):
            return False
        p.POV.vision[0].thystames += 1
        p.inventory.thystames -= 1
        return setRitual(p)
    return True