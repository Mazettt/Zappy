#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <thread>
#include <optional>
#include <queue>
#include "Socket.hpp"
#include "MyError.hpp"
#include "String.hpp"
#include "Args.hpp"
#include "Utils.hpp"
#include "Tile.hpp"

namespace my {
    class ServerLink {
        public:
            class Error: public MyError {
                public:
                    Error(const std::string &message, const std::string &className = "ServerLink"): MyError(className, message, true, "ERROR") {}
            };
            class Warning: public MyError {
                public:
                    Warning(const std::string &message, const std::string &className = "ServerLink"): MyError(className, message, true, "WARN") {}
            };
            class Info: public MyError {
                public:
                    Info(const std::string &message, const std::string &className = "ServerLink"): MyError(className, message, false, "INFO") {}
            };

            ServerLink(const Args &args);
            ServerLink(const ServerLink &other) = delete;
            ServerLink(ServerLink &&other);
            ~ServerLink();

            ServerLink &operator=(const ServerLink &other) = delete;
            ServerLink &operator=(ServerLink &&other);

            const std::string &getTeam() const;
            const std::pair<int, int> &getMapSize() const;
            int getLvl() const;

            void forward();
            void left();
            void right();
            std::vector<Tile> look();
            std::unordered_map<Resource, int> inventory();
            void broadcast(const std::string &message);
            int connectNbr();
            void fork();
            bool eject();
            bool take(Resource type);
            bool set(Resource type);
            int incantation();

            std::optional<std::pair<std::string, int>> getBroadcast();
            void clearBroadcast();

        protected:
        private:
            std::vector<std::string> _read(bool incantation = false);
            void _setBroadcast(const std::string &command);

            my::Socket _socket;
            std::string _team;
            std::pair<int, int> _mapSize;
            std::queue<std::pair<std::string, int>> _broadcast;
            int _lvl;
    };
}
