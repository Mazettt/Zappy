/*
** EPITECH PROJECT, 2022
** ai_leo
** File description:
** Socket.cpp
*/

#include "Socket.hpp"

Socket::Socket()
{
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket == -1) {
        std::cerr << "Error: socket creation failed." << std::endl;
        exit(84);
    }
}

Socket::~Socket()
{
    close(_socket);
}

void Socket::connectSocket(std::string ip, int port)
{
    _server.sin_addr.s_addr = inet_addr(ip.c_str());
    _server.sin_family = AF_INET;
    _server.sin_port = htons(port);
    if (connect(_socket, (struct sockaddr *)&_server, sizeof(_server)) < 0) {
        std::cerr << "Error: connection failed." << std::endl;
        exit(84);
    }
}

void Socket::sendSocket(std::string message)
{
    if (send(_socket, message.c_str(), message.length(), 0) < 0) {
        std::cerr << "Error: send failed." << std::endl;
        exit(84);
    }
}

std::string Socket::receiveSocket()
{
    char buffer[1024] = {0};
    std::string message;

    if (read(_socket, buffer, 1024) < 0) {
        std::cerr << "Error: receive failed." << std::endl;
        exit(84);
    }
    message = buffer;
    return (message);
}

void Socket::closeSocket()
{
    close(_socket);
}
