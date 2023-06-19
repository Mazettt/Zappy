#pragma once

#include <iostream>
#include <vector>
#include "ServerLink.hpp"
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
            bool _isResourceInTile(const std::vector<ServerLink::Type> &tile, ServerLink::Type type) const;

            ServerLink _s;
            ElevCond _elevcond;
            size_t _foodEaten;
    };
}
