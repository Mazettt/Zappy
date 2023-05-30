/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Network.cpp
*/

#include "../../includes/MySocketHeader/Network.hpp"

using namespace ZappyGui;
using namespace ZappyNetworking;

Networking::Networking()
{
}

Networking::~Networking()
{
}

int Networking::createSocket()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == -1)
        throw MyError("Networking", "Error while creating socket.");
    else
        std::cout << "Socket created." << std::endl;
    return sock;
}

int Networking::connectToServer(int port, std::string ip)
{
    int sock = createSocket();
    struct sockaddr_in server;

    server.sin_addr.s_addr = inet_addr(ip.c_str());
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
        throw MyError("Networking", "Error while connecting to server.");
    else
        std::cout << "Connected to server." << std::endl;
    return sock;
}

int Networking::sendToServer(int sock, std::string message)
{
    send(sock, message.c_str(), strlen(message.c_str()), 0);
    return 0;
}

std::string Networking::receiveFromServer()
{
    int rtread;
    char buffer[1024] = {0};
    rtread = read(0, buffer, 1024);
    std::cout << "rtread => " << rtread << std::endl;
    std::cout << "ouais => " << buffer << std::endl;
    return 0;
}
