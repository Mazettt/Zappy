/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** Conn.cpp
*/

#include "Conn.hpp"

ZappyAI::Conn::Conn(int port, std::string const &machine)
{
    _port = port;
    _machine = machine;
    _fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_fd < 0)
        throw MyError("Error: socket creation failed");
    _serv_addr.sin_family = AF_INET;
    _serv_addr.sin_port = htons(port);
    if (_machine == "localhost")
        _machine = "127.0.0.1";
    std::cout << _machine << std::endl;
    if (inet_pton(AF_INET, _machine.c_str(), &_serv_addr.sin_addr) <= 0)
        throw MyError("Error: invalid address");
}

void ZappyAI::Conn::connectToServer()
{
    if (_machine == "localhost")
        _machine = "127.0.0.1";
    if (connect(_fd, (struct sockaddr *)&_serv_addr, sizeof(_serv_addr)) < 0)
        throw MyError("Error: connection failed");
}

void ZappyAI::Conn::sendToServer(std::string const &message)
{
    if (send(_fd, message.c_str(), message.length(), 0) < 0)
        throw MyError("Error: send failed");
}

std::string ZappyAI::Conn::receiveFromServer()
{
    char buffer[1024] = {0};
    int valread = read(_fd, buffer, 1024);
    if (valread < 0)
        throw MyError("Error: read failed");
    return std::string(buffer);
}

void ZappyAI::Conn::closeConnection()
{
    close(_fd);
}

std::string ZappyAI::Conn::receiveVision()
{
    std::string response = receiveFromServer();
    while (response.find("]") == std::string::npos) {
        response += receiveFromServer();
    }
    return response;
}

std::string ZappyAI::Conn::receiveInventory()
{
    std::string response = receiveFromServer();
    while (response.find("]") == std::string::npos) {
        response += receiveFromServer();
    }
    return response;
}

int ZappyAI::Conn::getFd() const
{
    return _fd;
}

int ZappyAI::Conn::getPort() const
{
    return _port;
}

std::vector<std::string> ZappyAI::Conn::initPlayer(std::string const &teamName)
{
    receiveFromServer();
    std::string message = teamName + "\n";
    sendToServer(message);
    std::string mess = receiveFromServer();
    std::string client_num = mess.substr(0, mess.find("\n"));
    if (client_num == "ko") {
        std::cerr << "Error: team name is invalid or server does not accept more players" << std::endl;
        exit(84);
    }
    std::string size_map = mess.substr(mess.find("\n") + 1, mess.length());
    std::cout << "Client num: " << client_num << std::endl;
    std::cout << "Size map: " << size_map << std::endl;
    std::vector<std::string> infos;
    infos.push_back(client_num);
    infos.push_back(size_map);
    return infos;
}