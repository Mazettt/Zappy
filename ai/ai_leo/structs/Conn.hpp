/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** Conn.hpp
*/

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>
#include <netinet/in.h>
#include "MyError.hpp"

namespace ZappyAI {
    class Conn {
        public:
            Conn(int port, std::string const &machine);
            ~Conn() = default;
            void connectToServer();
            void sendToServer(std::string const &message);
            std::string receiveFromServer();
            void closeConnection();
            int getFd() const;
            int getPort() const;
            std::vector<std::string> initPlayer(std::string const &teamName);
            std::string receiveVision();
        private:
            int _fd;
            int _port;
            std::string _machine;
            struct sockaddr_in _serv_addr;            
    };
};