#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include "Player.hpp"
#include "Args.hpp"
#include "MyError.hpp"
#include "String.hpp"
#include "ElevCond.hpp"
#include "FoodHandler.hpp"

namespace my {
    class Core {
        public:
            Core(const Args &args);
            Core(const Core &other) = delete;
            Core(Core &&other) = delete;
            ~Core();

            Core &operator=(const Core &other) = delete;
            Core &operator=(Core &&other) = delete;

            void run();

        protected:
        private:
            enum State {
                FIND_FOOD,
                COME_TO_INCANTATION,
                FIND_RESOURCES,
                TRY_INCANT
            };

            void _findFood(const std::map<my::Resource, int> &inventory);
            void _comeToIncantation(const std::map<my::Resource, int> &inventory);
            void _findResources(const std::map<my::Resource, int> &inventory);
            void _incant(const std::map<my::Resource, int> &inventory);

            void _handleBroadcast();
            void _waitBroadcast(const std::string &toFind, std::function<bool (std::pair<std::string, int>)> callback);
            void _fork();

            FoodHandler _foodHandler;

            ElevCond _elevcond;
            const Args &_args;
            Player _player;
            std::vector<Player> _childs;
            State _state;

            int _comingPlayers;
            int _comingDir;
    };
}
