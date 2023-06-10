/*
** EPITECH PROJECT, 2022
** gui
** File description:
** popup.cpp
*/

#include "../includes/Popup.hpp"

using namespace ZappyGui;

Popup::Popup(const MyRayLib::Texture2D &background): _background(background) {
    int width = this->_background.getTexture().width;
    int height = this->_background.getTexture().height;

    this->_x = (GetScreenWidth() - width) / 2;
    this->_y = (GetScreenHeight() - height) / 2;

    this->_titleColor = MyRayLibColor::LightGray();
    this->_textColor = MyRayLibColor::Gray();

    this->_title = "";
    this->_description = "";
}

Popup::Popup(const MyRayLib::Texture2D &background, const std::string &title, const std::string &description): _background(background) {
    int width = this->_background.getTexture().width;
    int height = this->_background.getTexture().height;

    this->_x = (GetScreenWidth() - width) / 2;
    this->_y = (GetScreenHeight() - height) / 2;

    this->_titleColor = MyRayLibColor::DarkGray();
    this->_textColor = MyRayLibColor::DarkGray();

    this->_title = "";
    this->_description = "";
}

Popup::~Popup() {}

void Popup::setTitle(const std::string &title) {
        this->_title = title;
}

void Popup::setDescription(const std::string &description) {
        this->_description = description;
}

void Popup::show() {
    DrawTexture(this->_background.getTexture(), this->_x, this->_y, WHITE);
    DrawText(this->_title.c_str(), this->_x + 162, this->_y + 78, 30, this->_titleColor);
    DrawText(this->_description.c_str(), this->_x + 170, this->_y + 140, 20, this->_textColor);
}
