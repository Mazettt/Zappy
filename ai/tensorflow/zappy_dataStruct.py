##
## EPITECH PROJECT, 2023
## B-YEP-400-MLH-4-1-zappy-martin.d-herouville
## File description:
## zappy_dataStruct
##

class Player:
    def __init__(self, port, team="", machine="localhost"):
        self.stats = Stats(team)
        self.inventory = Tile(0, 0, 0, 0, 0, 0, 0)
        self.requirement = Tile(1, 1, 0, 0, 0, 0, 0)
        self.client = Client(port, machine)
        self.POV = POV
        self.remindToTurn = "No"

class Stats:
    def __init__(self, team):
        self.isAlive = True
        self.elevating = False
        self.level = 1
        self.X = 0
        self.Y = 0
        self.orient = 0 # 0 = N, 1 = E, 2 = S, 3 = W
        self.team = team
        self.playerNB = 0
        self.POV = POV
        self.inventory = Tile(0, 0, 0, 0, 0, 0, 0)
    def get_state(self):
        return [self.inventory, self.POV, self.level]

class Tile:
    def __init__(self, nearbyPlayers, linemates, deraumeres, siburs, mendianes, phiras, thystames):
        self.food = 0
        self.nearbyPlayers = nearbyPlayers
        self.linemates = linemates
        self.deraumeres = deraumeres
        self.siburs = siburs
        self.mendianes = mendianes
        self.phiras = phiras
        self.thystames = thystames

class Client:
    def __init__(self, port, machine):
        self.port = port
        self.machine = machine
        self.sock = 0
        self.buffer = []

class POV:
        vision = [Tile(0, 0, 0, 0, 0, 0, 0)]
        visionSize = 0
        visionCenter = 0
