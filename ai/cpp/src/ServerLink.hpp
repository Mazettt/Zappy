#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <thread>
#include "Socket.hpp"
#include "MyError.hpp"
#include "String.hpp"
#include "Args.hpp"
#include <optional>

namespace my {
    class ServerLink {
        public:
            enum Type {
                PLAYER,
                FOOD,
                LINEMATE,
                DERAUMERE,
                SIBUR,
                MENDIANE,
                PHIRAS,
                THYSTAME,
                NONE
            };

            static std::string typeToString(Type type);

            ServerLink(const Args &args);
            ServerLink(const ServerLink &other) = delete;
            ServerLink(ServerLink &&other) = delete;
            ~ServerLink();

            ServerLink &operator=(const ServerLink &other) = delete;
            ServerLink &operator=(ServerLink &&other) = delete;

            const std::string &team() const;
            const std::pair<int, int> &mapSize() const;

            void forward();
            void left();
            void right();
            std::vector<std::vector<Type>> look();
            std::map<Type, int> inventory();
            void broadcast(const std::string &message);
            int connectNbr();
            void fork();
            bool eject();
            bool take(Type type);
            bool set(Type type);
            int incantation();

            std::optional<std::string> getBroadcast();

        protected:
        private:
            std::vector<std::string> _read();
            void _setBroadcast(const std::string &command);

            my::Socket _socket;
            std::string _team;
            std::pair<int, int> _mapSize;
            std::string _broadcast;
    };
}
