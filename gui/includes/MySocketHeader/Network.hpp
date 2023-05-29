/*
** EPITECH PROJECT, 2022
** gui
** File description:
** ServerConnection.hpp
*/

#pragma once

#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "../../Utils/MyError.hpp"

namespace ZappyNetworking {
    class Networking {
        public:
            Networking();
            ~Networking();
            int createSocket();
            int connectToServer(int port, std::string ip);
            int sendToServer(int sock, std::string message);
            std::string receiveFromServer();
        protected:
        private:
    };
}
