/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Button.hpp
*/

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <raylib.h>
#include <functional>

namespace MyRayLib {
    class Button {
        private:
            std::function<void()> _callback;
        public:
            ::Sound SoundButton;
            ::Texture2D button;
            float frameHeight;
            ::Rectangle sourceRec;
            ::Rectangle btnBounds;
            int btnState;
            bool btnAction;
            Vector2 mousePoint;
            Button(const MyRayLib::Texture2D &texture, const std::string &pathSound, std::function<void()> callback) {
                this->button = texture.getTexture();
                this->SoundButton = LoadSound(pathSound.c_str());
                this->frameHeight = (float)this->button.height/3;
                this->sourceRec = { 0, 0, (float)button.width, frameHeight };
                this->mousePoint = {0.0f, 0.0f};
                this->btnState = 0;
                this->btnAction = false;
                this->_callback = callback;
            }
            ~Button(){};
            void ButtonSetPosition(float x, float y, float width, float height) {
                this->btnBounds = { x, y, width, height };
            }
            Vector2 MyGetMousePosition() {
                return this->mousePoint;
            }
            bool MyCheckCollisionPointRec(Vector2 point, Rectangle rec) {
                return CheckCollisionPointRec(point, rec);
            }
            bool MyIsMouseButtonDown(int button) {
                return IsMouseButtonDown(button);
            }
            bool MyIsMouseButtonReleased(int button) {
                return IsMouseButtonReleased(button);
            }
            void MyPlaySound(::Sound sound) {
                PlaySound(sound);
            }
            void MyDrawTextureRec(::Color tint) {
                DrawTextureRec(this->button, this->sourceRec, { this->btnBounds.x, this->btnBounds.y }, tint);
            }
            void MyUnloadTexture(::Texture2D texture) {
                UnloadTexture(texture);
            }
            void MyUnloadSound(::Sound sound) {
                UnloadSound(sound);
            }
            void HandleButton() {
                mousePoint = GetMousePosition();
                btnAction = false;

                if (MyCheckCollisionPointRec(mousePoint, btnBounds)) {
                    if (MyIsMouseButtonDown(MOUSE_BUTTON_LEFT))
                        btnState = 2;
                    else
                        btnState = 1;

                    if (MyIsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                        btnAction = true;
                }
                else
                    btnState = 0;

                sourceRec.y = btnState*frameHeight;
                if (btnAction) {
                    MyPlaySound(SoundButton);
                    _callback();
                }
            }
        };
}