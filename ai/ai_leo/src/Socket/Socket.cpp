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
    if (ip == "localhost")
        ip = "127.0.0.1";
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
    if (write(_socket, message.c_str(), message.length()) < 0) {
        std::cerr << "Error: send failed." << std::endl;
        exit(84);
    }
}

void Socket::sendSocket_try(std::string message)
{
    fd_set writefds;
    struct timeval tv;

    FD_ZERO(&writefds);
    FD_SET(_socket, &writefds);
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    if (select(_socket + 1, NULL, &writefds, NULL, &tv) < 0) {
        std::cerr << "Error: select failed." << std::endl;
        exit(84);
    }
    if (FD_ISSET(_socket, &writefds)) {
        if (send(_socket, message.c_str(), message.length(), 0) < 0) {
            std::cerr << "Error: send failed." << std::endl;
            exit(84);
        }
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

std::string Socket::receiveSocket_try()
{
    char buffer[1024] = {0};
    std::string message;
    fd_set readfds;
    struct timeval tv;

    FD_ZERO(&readfds);
    FD_SET(_socket, &readfds);
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    if (select(_socket + 1, &readfds, NULL, NULL, &tv) < 0) {
        std::cerr << "Error: select failed." << std::endl;
        exit(84);
    }
    if (FD_ISSET(_socket, &readfds)) {
        if (read(_socket, buffer, 1024) < 0) {
            std::cerr << "Error: receive failed." << std::endl;
            exit(84);
        }
        message = buffer;
        return (message);
    }
    return ("");
}

void Socket::closeSocket()
{
    close(_socket);
}
