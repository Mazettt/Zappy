/*
** EPITECH PROJECT, 2022
** cpp
** File description:
** ForkHandler.hpp
*/

namespace my {
    class ForkHandler {
        private:
            int _failIncantationCounter;
            int _teamMaximumSize;
            int _teamFreeSlots;

            double _thresholdDecision;
            double _weightLevel;
            double _weightFails;
            double _weightSlots;

            bool _decision;

        public:
            ForkHandler();
            ~ForkHandler();
            void calculate(int playerLevel, int teamMaximumSize, int teamFreeSlots);
            bool getForkDecision();
    };
}
