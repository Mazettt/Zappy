import numpy

class Player:
    def __init__(self, port, team="", machine="localhost"):
        self.stats = Stats(team)
        self.inventory = Inventory
        self.client = Client(port, machine)
        self.POV = POV

class Stats:
    def __init__(self, team):
        self.elevating = False
        self.level = 1
        self.lifeUnit = 50
        self.X = 0
        self.Y = 0
        self.orient = 0 # 0 = N, 1 = E, 2 = S, 3 = W
        self.team = team
        self.playerNB = 0

class Inventory:
        nearbyPlayers = 0
        linemates = 0
        deraumeres = 0
        siburs = 0
        mendianes = 0
        phiras = 0
        thystames = 0

class Client:
    def __init__(self, port, machine):
        self.port = port
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
