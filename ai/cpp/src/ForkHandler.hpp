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

            double _thresholdDecision;
            double _weightLevel;
            double _weightFails;

            bool _decision;

        public:
            ForkHandler();
            ~ForkHandler();
            void calculate(int playerLevel);
            bool getForkDecision();
            void incantationFailed();
            void incantationSuccess();
    };
}
