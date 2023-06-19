import random
import numpy as np
import tensorflow as tf
import keras
import pygame
import time
import socket
import zappy_parsing as zp
import zappy_network_utils as znu
import zappy_commands as zc
import zappy_dataStruct as zds
import zappy_manualAI as zma
import sys
import signal

print("TensorFlow version:", tf.__version__)

from keras.models import Sequential
from keras.layers import Dense
from keras.optimizers import Adam
from keras.models import load_model


class DQNAgent:
    inventory = []
    vision = []
    action = 0
    reward = 0
    done = False
    epsilon = 1
    gamma = 0.9
    learning_rate = 0.001
    memory = []
    action_space = 12
    state_space = 0
    batch_size = 32
    training = True
    model = None

    def __init__(self, state_space, action_space):
        self.state_space = state_space
        self.action_space = action_space
        self.model = self.build_model()

    def build_model(self):
        model = Sequential()
        model.add(Dense(32, input_dim=self.state_space, activation="relu"))
        model.add(Dense(32, activation="relu"))
        model.add(Dense(self.action_space, activation="linear"))
        model.compile(loss="mse", optimizer=Adam(lr=self.learning_rate))
        return model
    
    def save_model(self, fn):
        self.model.save(fn)

    def act(self, state):
        if np.random.rand() <= self.epsilon and self.training:
            return random.randrange(self.action_space)
        act_values = self.model.predict(state)
        return np.argmax(act_values[0])
    
    def remember(self, state, action, reward, next_state, done):
        self.memory.append((state, action, reward, next_state, done))

    def replay_new(self):
        if len(self.memory) < self.batch_size:
            return
        sample = random.sample(self.memory, self.batch_size)
        for state, action, reward, next_state, done in sample:
            target = self.model.predict(state)
            if done:
                target[0][action] = reward
            else:
                Q_future = max(self.model.predict(next_state)[0])
                target[0][action] = reward + Q_future * self.gamma
            self.model.fit(state, target, epochs=1, verbose=0)

    def train(self, state, action, reward, next_state, done):
        target = self.model.predict(state)
        if done:
            target[0][action] = reward
        else:
            Q_future = max(self.model.predict(next_state)[0])
            target[0][action] = reward + Q_future * self.gamma
        self.model.fit(state, target, epochs=1, verbose=0)

    def load(self, name):
        self.model = load_model(name) 

def train_agent(p, agent, clt):
    level = 1
    while True:
        last_action = ""
        action = agent.act(p.stats.get_state())

        memory = []
        inv = []
        if action == 0:
            if (zc.forward(clt)) == "dead\n":
                reward = -100
                agent.reward = reward
                agent.remember(p.stats.get_state(), action, reward, p.stats.get_state(), True)
                break
            reward = 1
            if (last_action == "forward"):
                reward = -2
            if (last_action == "right"):
                reward = 10
            if (last_action == "left"):
                reward = 10
            last_action = "forward"
            agent.reward = reward
            agent.remember(p.stats.get_state(), action, reward, p.stats.get_state(), False)
        elif action == 1:
            if (zc.right(clt)) == "dead\n":
                reward = -100
                agent.reward = reward
                agent.remember(p.stats.get_state(), action, reward, p.stats.get_state(), True)
                break
            reward = 1
            if (last_action == "right"):
                reward = -50
            if (last_action == "left"):
                reward = -5000
            zc.forward(clt)
            last_action = "right"
            agent.reward = reward
            agent.remember(p.stats.get_state(), action, reward, p.stats.get_state(), False)
        elif action == 2:
            if (zc.left(clt)) == "dead\n":
                reward = -100
                agent.reward = reward
                agent.remember(p.stats.get_state(), action, reward, p.stats.get_state(), True)
                break
            reward = 1
            if (last_action == "left"):
                reward = -50
            if (last_action == "right"):
                reward = -5000
            zc.forward(clt)
            last_action = "left"
            agent.reward = reward
            agent.remember(p.stats.get_state(), action, reward, p.stats.get_state(), False)
        elif action == 3:
            if (zc.look(clt)) == "dead\n":
                reward = -100
                agent.reward = reward
                agent.remember(p.stats.get_state(), action, reward, p.stats.get_state(), True)
                break
            reward = 1
            agent.reward = reward
            agent.remember(p.stats.get_state(), action, reward, p.stats.get_state(), False)
        elif action == 4:
            memory = zc.inventory(clt)
            reward = 1
            agent.reward = reward
            agent.remember(p.stats.get_state(), action, reward, p.stats.get_state(), False)
            if (memory.food < 3):
                reward = -500
                agent.reward = reward
                agent.remember(p.stats.get_state(), action, reward, p.stats.get_state(), True)
        elif action == 5:
            resp = zc.take(clt, "food")
            if resp == "dead\n":
                reward = -100
                agent.reward = reward
                agent.remember(p.stats.get_state(), action, reward, p.stats.get_state(), True)
                break
            if resp == "ko\n":
                reward = -100
                agent.reward = reward
                agent.remember(p.stats.get_state(), action, reward, p.stats.get_state(), False)
            reward = 555
            agent.reward = reward
            agent.remember(p.stats.get_state(), action, reward, p.stats.get_state(), False)
        elif action == 6:
            if (zc.take(clt, "linemate")) == "dead\n":
                reward = -100
                agent.reward = reward
                agent.remember(p.stats.get_state(), action, reward, p.stats.get_state(), True)
                break
            reward = 1
            agent.reward = reward
            agent.remember(p.stats.get_state(), action, reward, p.stats.get_state(), False)
        elif action == 7:
            if (zc.take(clt, "deraumere")) == "dead\n":
                reward = -100
                agent.reward = reward
                agent.remember(p.stats.get_state(), action, reward, p.stats.get_state(), True)
                break
            reward = 1
            agent.reward = reward
            agent.remember(p.stats.get_state(), action, reward, p.stats.get_state(), False)
        elif action == 8:
            if (zc.take(clt, "sibur")) == "dead\n":
                reward = -100
                agent.reward = reward
                agent.remember(p.stats.get_state(), action, reward, p.stats.get_state(), True)
                break
            reward = 1
            agent.reward = reward
            agent.remember(p.stats.get_state(), action, reward, p.stats.get_state(), False) 
        elif action == 9:
            if (zc.take(clt, "mendiane")) == "dead\n":
                reward = -100
                agent.reward = reward
                agent.remember(p.stats.get_state(), action, reward, p.stats.get_state(), True)
                break
            reward = 1
            agent.reward = reward
            agent.remember(p.stats.get_state(), action, reward, p.stats.get_state(), False) 
        elif action == 10:
            if (zc.take(clt, "phiras")) == "dead\n":
                reward = -100
                agent.reward = reward
                agent.remember(p.stats.get_state(), action, reward, p.stats.get_state(), True)
                break
            reward = 1
            agent.reward = reward
            agent.remember(p.stats.get_state(), action, reward, p.stats.get_state(), False) 
        elif action == 11:
            if (zc.take(clt, "thystame")) == "dead\n":
                reward = -100
                agent.reward = reward
                agent.remember(p.stats.get_state(), action, reward, p.stats.get_state(), True)
                break
            reward = 1
            agent.reward = reward
            agent.remember(p.stats.get_state(), action, reward, p.stats.get_state(), False) 
        # elif action == 12:
            # zc.fork(clt)
        # elif action == 13:
            # zc.eject(clt)
        # elif action == 14:
            # zc.broadcast(clt, "hello world")
    
    print("Training done")
    agent.save_model("./save/agent.h5")


def main():
    for i in range(200):
        print("Training number: {}".format(i))
        args = zp.get_args()
        p = zds.Player(args["port"], args["name"], args["machine"])
        p.client.sock = znu.con_to_server(p.client.machine, p.client.port)
        znu.recv_from_server(p.client.sock)
        p_infos = znu.get_player_infos(p.client.sock, p.stats.team)
        zp.print_log("Player: {}".format(p_infos))
        client_num, map_x, map_y = zp.parse_player_infos(p_infos)
        p.stats.playerNB = client_num
        print("Player number: {}".format(p.stats.playerNB))
        ai_training = True
        clt = zds.Client(p.client.port, p.client.machine)
        clt.sock = p.client.sock
        if ai_training:
            agent = DQNAgent(8, 12)
            try:
                agent.load("./save/agent.h5")
                print("Agent loaded")
            except:
                pass
            agent.epsilon = 1
            agent.training = True
            agent.batch_size = 32
            agent.gamma = 0.9
            agent.learning_rate = 0.001
            agent.memory = []
            agent.model = agent.build_model()
            agent.model.summary()
            agent.epsilon = 1
            agent.training = True
            agent.batch_size = 32
            agent.gamma = 0.9
            agent.learning_rate = 0.001
            agent.memory = []
            agent.model = agent.build_model()
            try:
                agent.load("./save/ai_model.h5")
            except:
                pass
            train_agent(p, agent, clt)

if __name__ == "__main__":
    main()