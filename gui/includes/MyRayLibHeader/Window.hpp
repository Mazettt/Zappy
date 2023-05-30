/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** RayLib.hpp
*/

#pragma once

#include <iostream>
#include "raylib.h"

namespace MyRayLib {
    class MyRayLibWindow {
        public:
            MyRayLibWindow(int width, int height, const char *title);
            ~MyRayLibWindow();
            bool MyWindowShouldClose(void);
            void MyClearBackground(Color color);
            void MySetTargetFPS(int fps);
        protected:
        private:
    };
}
