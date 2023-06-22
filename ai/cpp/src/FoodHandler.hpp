/*
** EPITECH PROJECT, 2022
** cpp
** File description:
** FoodHandler.hpp
*/

#pragma once
#include <utility>

namespace my {
    class FoodHandler {
        private:
            int _incantationScore;
            std::pair<int, int> _mapSize;
            double _factorLevel;
            double _factorMapSize;
            double _factorIncantationScore;

            int _minimumFood;
            int _maximumFood;

        public:
            FoodHandler(int x, int y);
            ~FoodHandler();
            int getMinimumFood(int playerLevel);
            int getMaximumFood(int playerLevel);
            void calculate(int playerLevel);
            void incantationFail();
            void incantationSuccess();
            int getIncantationScore();
    };
}
