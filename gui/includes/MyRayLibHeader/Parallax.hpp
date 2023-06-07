/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Parallax.hpp
*/

#pragma once

#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <string>

namespace MyRayLib {
    class Parallax {
        private:
            ::Texture2D _background;
            ::Texture2D _midground;
            float _scrollingBack = 0.0f;
            float _scrollingMid = 0.0f;
            Font _fontTtf;
        public:
            Parallax(const std::string background, const std::string middle) {
                _fontTtf = LoadFontEx("./assets/Parallax/Dongle-Bold.ttf", 512, 0, 250);
                _background = LoadTexture(background.c_str());
                _midground = LoadTexture(middle.c_str());
                _scrollingBack = 0.0f;
                _scrollingMid = 0.0f;
            }
            ~Parallax(){};
            void updateInLoop() {
                _scrollingBack -= 0.5f;
                _scrollingMid -= 1.0f;
                if (_scrollingBack <= -_background.width*2) _scrollingBack = 0;
                if (_scrollingMid <= -_midground.width) _scrollingMid = 400;

                DrawTextureEx(_background, (Vector2){ _scrollingBack, 20 }, 0.0f, 1.0f, WHITE);
                DrawTextureEx(_background, (Vector2){ _background.width*2 + _scrollingBack, 20 }, 0.0f, 1.0f, WHITE);

                DrawTextureEx(_midground, (Vector2){ _scrollingMid, 20 }, 0.0f, 1.0f, WHITE);
                DrawTextureEx(_midground, (Vector2){ _midground.width*2 + _scrollingMid, 20 }, 0.0f, 1.0f, WHITE);
            }
            void UnLoadAllParallax() {
                UnloadTexture(_background);
                UnloadTexture(_midground);
            }
            void WriteTitle() {
                DrawTextEx(_fontTtf, "Garfield's dream", (Vector2){ 740.0f, 100.0f }, 130.0, 2, BLUE);
            }
            void UnLoadFont() {
                UnloadFont(_fontTtf);
            }
        };
}
