/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** ShowPlayerData.cpp
*/

#include "../../includes/MapHeader/ShowPlayerData.hpp"

MyRayLib::ShowPlayerData::ShowPlayerData()
{
    this->_image = LoadImage("./gui/assets/oe.png");     // Load image in CPU memory (RAM)

    this->_font = LoadFont("./Dongle-Bold.ttf");

    ImageDrawTextEx(&this->_image, this->_font, "PARROTS & CAT", (Vector2){ 300, 230 }, (float)this->_font.baseSize, -2, WHITE);

    this->_texture = LoadTextureFromImage(this->_image);
    this->_posX = 15.0;
    this->_posY = 40.0;
    this->_index = 0;
}

MyRayLib::ShowPlayerData::~ShowPlayerData()
{
}

void MyRayLib::ShowPlayerData::ShowDataForEachPlayer(std::vector<std::shared_ptr<ZappyGui::Player>> _players)
{
    this->_posX = 30.0;
    this->_posY = 60.0;
    if (_players.size() == 0)
        return;
    if (IsKeyPressed(KEY_ENTER)) {
        if (this->_index >= (_players.size() - 1))
            this->_index = 0;
        else
            this->_index++;
    }

    for (int i = 0; i < _players.size(); ++i) {
        if (i == this->_index) {
            DrawText(std::to_string(_players.at(i)->getPlayerNumber()).c_str(), this->_posX, this->_posY, 20, ORANGE);
            DrawTexture(this->_texture, 20, 830, WHITE);
            DrawText(_players.at(i)->getTeamName().c_str(), 30, 850, 20, BLACK);
        } else
            DrawText(std::to_string(_players.at(i)->getPlayerNumber()).c_str(), this->_posX, this->_posY, 20, BLACK);
        if (this->_posY >= 750) {
            this->_posY = 60.0;
            this->_posX += 60.0;
        } else
            this->_posY += 60.0;
    }
}
