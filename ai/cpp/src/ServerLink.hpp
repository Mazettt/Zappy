#pragma once

#include <iostream>
#include <vector>
#include <map>
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
            std::map<Resource, int> inventory();
            void broadcast(const std::string &message);
            int connectNbr();
            void fork();
            bool eject();
            bool take(Resource type);
            bool set(Resource type);
            int incantation();

            std::optional<std::pair<std::string, int>> getBroadcast();

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
