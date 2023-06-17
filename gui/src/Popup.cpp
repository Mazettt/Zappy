/*
** EPITECH PROJECT, 2022
** gui
** File description:
** popup.cpp
*/

#include "../includes/Popup.hpp"

using namespace ZappyGui;

Popup::Popup() {
    this->_show = false;
    this->_titleColor = MyRayLibColor::DarkGray();
    this->_textColor = MyRayLibColor::DarkGray();
    this->_title = "";
    this->_description = "";
}

Popup::~Popup() {}

void Popup::setTexture(const MyRayLib::Texture2D &background) {
    this->_background = background.getTexture();
    int width = this->_background.width;
    int height = this->_background.height;

    this->_x = (MyRayLib::MyRayLibWindow::MyGetScreenWidth() - width) / 2;
    this->_y = (MyRayLib::MyRayLibWindow::MyGetScreenHeight() - height) / 2;

}

void Popup::setTitle(const std::string &title) {
        this->_title = title;
}

void Popup::setDescription(const std::string &description) {
        this->_description = description;
}

void Popup::setStatus(bool status) {
    if (status == true)
        MyRayLib::MyRayLibWindow::setExitKey(KEY_NULL);
    else
        MyRayLib::MyRayLibWindow::setExitKey(KEY_ESCAPE);
    this->_show = status;
}

bool Popup::getStatus() {
    return this->_show;
}

void Popup::show() {
    if (_show == false)
        return;
    MyRayLib::Draw::MyDrawTexture(this->_background, this->_x, this->_y, WHITE);
    MyRayLib::Draw::MyDrawText(this->_title.c_str(), this->_x + 162, this->_y + 78, 30, this->_titleColor);
    MyRayLib::Draw::MyDrawText(this->_description.c_str(), this->_x + 170, this->_y + 140, 20, this->_textColor);
}
