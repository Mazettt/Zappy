#!/usr/bin/python3

import sys
import socket
import select
import time
import random
import tensorflow as tf
import numpy as np
import math
import os

def print_usage():
    print("USAGE: ./zappy_ai -p port -n name -h machine\n\tport\tis the port number\n\tname\tis the name of the team\n\tmachine\tis the name of the machine; localhost by default")

def get_args():
    args = {
        "port": 0,
        "name": "",
        "machine": "localhost"
    }
    for i in range(1, len(sys.argv)):
        if sys.argv[i] == "-p":
            args["port"] = int(sys.argv[i + 1])
        elif sys.argv[i] == "-n":
            args["name"] = sys.argv[i + 1]
        elif sys.argv[i] == "-h":
            args["machine"] = sys.argv[i + 1]
    if args["port"] == 0 or args["name"] == "":
        print_usage()
        exit(84)
    return args
