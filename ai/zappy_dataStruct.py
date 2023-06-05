import numpy

class Player:
    def __init__(self, port, team="", machine="localhost"):
        self.stats = Stats
        self.inventory = Inventory
        self.client = Client(port, team, machine)
        self.POV = POV

class Stats:
        elevating = False
        level = 1
        lifeUnit = 50
        X = 0
        Y = 0
        orient = 0 # 0 = N, 1 = E, 2 = S, 3 = W
        team = ""
        playerNB = 0

class Inventory:
        nearbyPlayers = 0
        linemates = 0
        deraumeres = 0
        siburs = 0
        mendianes = 0
        phiras = 0
        thystames = 0

class Client:
    def __init__(self, port, team, machine):
        self.port = port
        self.team = team
        self.machine = machine
        self.sock = 0

class POV:
        vision = []
        visionSize = 0
        visionCenter = 0





#class Row: vector<class tile>
#
#class Tile: vector<entities> (entities = Player / food / stone)
#
#

# Create an instance of the struct
# my_struct = Data(10, 'Hello', True)

# Access the fields
# print(my_struct.port)  # Output: 10
# print(my_struct.team)  # Output: Hello
# print(my_struct.machine)  # Output: True
