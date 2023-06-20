#pragma once

#include <iostream>
#include <vector>
#include "Player.hpp"
#include "Args.hpp"
#include "MyError.hpp"
#include "String.hpp"
#include "ElevCond.hpp"

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
            void _fork();
            void _lookForFood(Player &player);
            const Args &_args;
            Player _player;
            std::vector<Player> _childs;
    };
}
