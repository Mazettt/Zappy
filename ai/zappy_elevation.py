import ai.zappy_dataStruct as zds
import ai.zappy_commands as zc

def canElevate(p: zds.Player):
    p.stats.elevating = False
    if (p.inventory.nearbyPlayers < p.requirement.nearbyPlayers):
        return
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
        updatRequirement(p)

def updatRequirement(p: zds.Player):
    if (p.stats.level == 2):
        p.requirement = zds.Inventory(2, 1, 1, 1, 0, 0, 0)
    if (p.stats.level == 3):
        p.requirement = zds.Inventory(2, 2, 0, 1, 0, 2, 0)
    if (p.stats.level == 4):
        p.requirement = zds.Inventory(4, 1, 1, 2, 0, 1, 0)
    if (p.stats.level == 5):
        p.requirement = zds.Inventory(4, 1, 2, 1, 3, 0, 0)
    if (p.stats.level == 6):
        p.requirement = zds.Inventory(6, 1, 2, 3, 0, 1, 0)
    if (p.stats.level == 7):
        p.requirement = zds.Inventory(6, 2, 2, 2, 2, 2, 1)