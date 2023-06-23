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
            double _mapSize;
            double _factorLevel;
            double _factorMapSize;
            double _factorIncantationScore;

            int _minimumFood;
            int _maximumFood;

        public:
            FoodHandler(int x, int y);
            ~FoodHandler();
            void setMapSize(int x, int y);
            int getMinimumFood();
            int getMaximumFood();
            void calculate(int playerLevel);
            void incantationFail();
            void incantationSuccess();
            int getIncantationScore();
    };
}
