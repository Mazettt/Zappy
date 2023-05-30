import sys
import socket
import select
import time
import random
import tensorflow as tf
import numpy as np
import math
import os
import zappy_parsing as zp

def con_to_server(args):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((args["machine"], args["port"]))
    zp.print_log("Connected to {} on port {}".format(args["machine"], args["port"]))
    return sock