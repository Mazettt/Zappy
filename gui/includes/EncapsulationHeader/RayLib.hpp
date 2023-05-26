/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** RayLib.hpp
*/

#pragma once

#include <iostream>
#include "raylib.h"

namespace ZappyGui {
    class MyRayLib {
        public:
            MyRayLib(){};
            ~MyRayLib(){};
            void MyInitWindow(int width, int height, const char *title);
            void MyCloseWindow(void);
            bool MyWindowShouldClose(void);
            void MyBeginDrawing(void);
            void MyClearBackground(Color color);
            void MyDrawText(const char *text, int posX, int posY, int fontSize, Color color);
            void MyEndDrawing(void);
        protected:
        private:
    };
}
