#pragma once

#include <iostream>
#include <vector>
#include <map>
#include "Utils.hpp"

namespace my {
    class Tile {
        public:
            Tile();
            Tile(const std::vector<Resource> &resources);
            Tile(const std::map<Resource, int> &resources);
            Tile(const Tile &other);
            Tile(Tile &&other);
            ~Tile();

            Tile &operator=(const Tile &other);
            Tile &operator=(Tile &&other);

            void addResource(Resource type);
            int getNbr(Resource type) const;

        protected:
        private:
            void _fillEmpty();
            std::map<Resource, int> _resources;
    };
}