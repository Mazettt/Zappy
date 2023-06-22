/*
** EPITECH PROJECT, 2022
** ai_leo
** File description:
** Socket.hpp
*/

#ifndef SOCKET_HPP_
#define SOCKET_HPP_

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class Socket {
    public:
        Socket();
        ~Socket();
        void connectSocket(std::string ip, int port);
        void sendSocket(std::string message);
        std::string receiveSocket();
        void closeSocket();
    private:
        int _socket;
        struct sockaddr_in _server;
};

#endif /* !SOCKET_HPP_ */