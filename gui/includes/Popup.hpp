/*
** EPITECH PROJECT, 2022
** gui
** File description:
** popup.hpp
*/

#pragma once
#include "./MyRayLibHeader/Texture.hpp"
#include "./MyRayLibHeader/Color.hpp"

using namespace MyRayLib;

namespace ZappyGui {
    class Popup {
        private:
            int _x;
            int _y;
            Color _titleColor;
            Color _textColor;
            const MyRayLib::Texture2D &_background;

            std::string _title;
            std::string _description;

        public:
            Popup(const MyRayLib::Texture2D &background);
            Popup(const MyRayLib::Texture2D &background, const std::string &title, const std::string &description);
            void setTitle(const std::string &title);
            void setDescription(const std::string &description);
            void show();
            ~Popup();
    };
}
