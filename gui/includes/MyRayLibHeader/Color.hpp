/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Color.hpp
*/

#pragma once
#include <string>
#include "raylib.h"

namespace MyRayLib {
    class MyRayLibColor {
        public:
            unsigned char red;
            unsigned char green;
            unsigned char blue;
            unsigned char alpha;
            MyRayLibColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) {
                this->red = red;
                this->green = green;
                this->blue = blue;
                this->alpha = alpha;
            };

            MyRayLibColor(unsigned char red, unsigned char green, unsigned char blue) {
                this->red = red;
                this->green = green;
                this->blue = blue;
                this->alpha = 255;
            };
            inline static Color LightGray() { return LIGHTGRAY; }
            inline static Color Gray() { return GRAY; }
            inline static Color DarkGray() { return DARKGRAY; }
            inline static Color Yellow() { return YELLOW; }
            inline static Color Gold() { return GOLD; }
            inline static Color Orange() { return ORANGE; }
            inline static Color Pink() { return PINK; }
            inline static Color Red() { return RED; }
            inline static Color Maroon() { return MAROON; }
            inline static Color Green() { return GREEN; }
            inline static Color Lime() { return LIME; }
            inline static Color DarkGreen() { return DARKGREEN; }
            inline static Color SkyBlue() { return SKYBLUE; }
            inline static Color Blue() { return BLUE; }
            inline static Color DarkBlue() { return DARKBLUE; }
            inline static Color Purple() { return PURPLE; }
            inline static Color Violet() { return VIOLET; }
            inline static Color DarkPurple() { return DARKPURPLE; }
            inline static Color Beige() { return BEIGE; }
            inline static Color Brown() { return BROWN; }
            inline static Color DarkBrown() { return DARKBROWN; }
            inline static Color White() { return WHITE; }
            inline static Color Black() { return BLACK; }
            inline static Color Blank() { return BLANK; }
            inline static Color Magenta() { return MAGENTA; }
            inline static Color RayWhite() { return RAYWHITE; }
            ~MyRayLibColor() {};
    };
}
