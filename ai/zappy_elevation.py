import zappy_dataStruct as zds
import zappy_network_utils as znu
import zappy_commands as zc

def canElevate(p: zds.Player):
    p.stats.elevating = False
    if (p.stats.level == 1):
        elevationAssess(p.inventory, 1, 1, 0, 0, 0, 0, 0)
    if (p.stats.level == 2):
        elevationAssess(p.inventory, 2, 1, 1, 1, 0, 0, 0)
    if (p.stats.level == 3):
        elevationAssess(p.inventory, 2, 2, 0, 1, 0, 2, 0)
    if (p.stats.level == 4):
        elevationAssess(p.inventory, 4, 1, 1, 2, 0, 1, 0)
    if (p.stats.level == 5):
        elevationAssess(p.inventory, 4, 1, 2, 1, 3, 0, 0)
    if (p.stats.level == 6):
        elevationAssess(p.inventory, 6, 1, 2, 3, 0, 1, 0)
    if (p.stats.level == 7):
        elevationAssess(p.inventory, 6, 2, 2, 2, 2, 2, 1)

def elevationAssess(p: zds.Player, playersNbr, linemates, deraumeres, siburs, mendianes, phiras, thystames):
    if (p.inventory.nearbyPlayers < playersNbr):
        return
    if (p.inventory.linemates < linemates):
        return
    if (p.inventory.deraumeres < deraumeres):
        return
    if (p.inventory.siburs < siburs):
        return
    if (p.inventory.mendianes < mendianes):
        return
    if (p.inventory.phiras < phiras):
        return
    if (p.inventory.thystames < thystames):
        return
    elevationTry(p)

def elevationTry(p: zds.Player):
    p.stats.elevating = True
    zc.incantation(p.client.sock)
    if (znu.recv_from_server(p.client.sock) == "Elevation underway\n"):
        p.stats.elevating = False
        p.stats.level += 1