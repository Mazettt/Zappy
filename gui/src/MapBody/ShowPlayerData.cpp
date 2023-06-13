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

std::string MyRayLib::ShowPlayerData::getRessourceName(ZappyGui::IResource::resourceType type)
{
    if (type == ZappyGui::IResource::resourceType::BURGER)
        return "Food";
    if (type == ZappyGui::IResource::resourceType::LINEMATE)
        return "Linemate";
    if (type == ZappyGui::IResource::resourceType::DERAUMERE)
        return "Deraumere";
    if (type == ZappyGui::IResource::resourceType::SIBUR)
        return "Sibur";
    if (type == ZappyGui::IResource::resourceType::MENDIANE)
        return "Mendiane";
    if (type == ZappyGui::IResource::resourceType::PHIRAS)
        return "Phiras";
    if (type == ZappyGui::IResource::resourceType::THYSTAME)
        return "Thystame";
    return "";
}

void MyRayLib::ShowPlayerData::ShowDataForEachPlayer(std::vector<std::shared_ptr<ZappyGui::Player>> _players)
{
    this->_posX = 30.0;
    this->_posY = 60.0;
    float ressourceX = 30.0;
    float ressourceY = 910.0;
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
            std::string _printLevel = "Level: " + std::to_string(_players.at(i)->getPlayerLevel());
            DrawText(_printLevel.c_str(), 30, 850, 20, BLACK);
            std::string _printTeam = "Team: " + _players.at(i)->getTeamName();
            DrawText(_printTeam.c_str(), 30, 880, 20, BLACK);
            const auto &tmpInventory = _players.at(i)->getInventory();
            int tmp = 0;
            for (auto itEnum = ZappyGui::IResource::BURGER; itEnum != ZappyGui::IResource::EGG; itEnum = static_cast<ZappyGui::IResource::resourceType>(itEnum + 1)) {
                try {
                    tmp = tmpInventory.at(itEnum);
                } catch (const std::exception &e) {
                    tmp = 0;
                }
                std::string _printRessource = this->getRessourceName(itEnum) + ": " + std::to_string(tmp);
                DrawText(_printRessource.c_str(), ressourceX, ressourceY, 20, BLACK);
                if (ressourceY >= 990.0) {
                    ressourceY = 910.0;
                    ressourceX += 200.0;
                } else
                    ressourceY += 30.0;
            }
        } else
            DrawText(std::to_string(_players.at(i)->getPlayerNumber()).c_str(), this->_posX, this->_posY, 20, BLACK);
        if (this->_posY >= 750) {
            this->_posY = 60.0;
            this->_posX += 60.0;
        } else
            this->_posY += 60.0;
    }
}
