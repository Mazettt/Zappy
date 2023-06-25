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
            const std::string &getTeam() const;
            const std::pair<int, int> &getMapSize() const;
            int getLevel() const;

            void lookForResource(Resource type);
            void goToTile(int tileIndex);
            void goToDirection(int direction);

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
            void lookForResources(const std::unordered_map<my::Resource, int> &needs);

        protected:
        private:
            ServerLink _s;
            ElevCond _elevcond;
            size_t _foodEaten;
    };
}