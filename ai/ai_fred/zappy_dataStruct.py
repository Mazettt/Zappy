##
## EPITECH PROJECT, 2023
## B-YEP-400-MLH-4-1-zappy-martin.d-herouville
## File description:
## zappy_dataStruct
##

from enum import Enum

class Player:
    def __init__(self, port, team="", machine="localhost"):
        self.stats = Stats(team)
        self.inventory = Tile(0, 0, 0, 0, 0, 0, 0)
        self.requirement = Tile(1, 1, 0, 0, 0, 0, 0)
        self.client = Client(port, machine)
        self.POV = POV
        self.AI = AI

class Behavior(Enum):
    SeekFood = 1
    SeekStones = 2
    SeekPlayer = 3
    Elevate = 4

class AI:
    remindToTurn = "No"
    remindToTurnDelay = 0
    directionToGo = -1
    seekElevatingPlayer = 0
    elevating = False
    forward = False
    behavior = Behavior.SeekFood

class Stats:
    def __init__(self, team):
        self.isAlive = True
        self.level = 1
        self.X = 0
        self.Y = 0
        self.orient = 0 # 0 = N, 1 = E, 2 = S, 3 = W
        self.team = team
        self.playerNB = 0

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

    def __str__(self):
        return f"Tile: nearbyPlayers={self.nearbyPlayers}, linemates={self.linemates}, deraumeres={self.deraumeres}, siburs={self.siburs}, mendianes={self.mendianes}, phiras={self.phiras}, thystames={self.thystames}"

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
