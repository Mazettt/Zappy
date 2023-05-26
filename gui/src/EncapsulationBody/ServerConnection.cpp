/*
** EPITECH PROJECT, 2022
** gui
** File description:
** ServerConnection.cpp
*/

#include "../../includes/EncapsulationHeader/ServerConnection.hpp"

using namespace ZappyGui;

ServerConnection::ServerConnection()
{
}

ServerConnection::~ServerConnection()
{
}

int ServerConnection::createSocket()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == -1)
        throw MyError("ServerConnection", "Error while creating socket.");
    else
        std::cout << "Socket created." << std::endl;
    return sock;
}

int ServerConnection::connectToServer(int port, std::string ip)
{
    int sock = createSocket();
    struct sockaddr_in server;

    server.sin_addr.s_addr = inet_addr(ip.c_str());
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
        throw MyError("ServerConnection", "Error while connecting to server.");
    else
        std::cout << "Connected to server." << std::endl;
    return sock;
}

int ServerConnection::sendToServer(int sock, std::string message)
{
    send(sock, message.c_str(), strlen(message.c_str()), 0);
    return 0;
}

std::string ServerConnection::receiveFromServer()
{
    int rtread;
    char buffer[1024] = {0};
    rtread = read(0, buffer, 1024);
    std::cout << "ouais => " << buffer << std::endl;
    return 0;
}
