#pragma once

#include <iostream>
#include "ServerLink.hpp"
#include "Args.hpp"
#include "ElevCond.hpp"

namespace my {
    class Player {
        public:
            Player(const Args &args);
            Player(const Player &other) = delete;
            Player(Player &&other);
            ~Player();

            Player &operator=(const Player &other) = delete;
            Player &operator=(Player &&other);

            bool canElevate();
            int getLevel() const;

            void lookForResource(Resource type);
            void goToTile(int tileIndex);

            void forward();
            void left();
            void right();
            const std::vector<Tile> &look();
            const std::map<Resource, int> &inventory();
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
            ServerLink _s;
            ElevCond _elevcond;
            std::map<Resource, int> _inventory;
            std::vector<Tile> _lastLook;
            size_t _foodEaten;
    };
}