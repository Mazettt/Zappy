/*
** EPITECH PROJECT, 2022
** gui
** File description:
** popup.hpp
*/

#pragma once
#include "./MyRayLibHeader/Texture.hpp"
#include "./MyRayLibHeader/Color.hpp"
#include "./MyRayLibHeader/Window.hpp"
#include "./MyRayLibHeader/Draw.hpp"

using namespace MyRayLib;

namespace ZappyGui {
    class Popup {
        private:
            int _x;
            int _y;
            bool _show;
            Color _titleColor;
            Color _textColor;
            ::Texture2D _background;

            std::string _title;
            std::string _description;

        public:
            Popup();
            void setTexture(const MyRayLib::Texture2D &background);
            void setTitle(const std::string &title);
            void setStatus(bool status);
            bool getStatus();
            void setDescription(const std::string &description);
            void show();
            ~Popup();
    };
}
