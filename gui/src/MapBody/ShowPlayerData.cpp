/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** ShowPlayerData.cpp
*/

#include "../../includes/MapHeader/ShowPlayerData.hpp"

MyRayLib::ShowPlayerData::ShowPlayerData()
{
    this->_image = LoadImage("./gui/assets/player_stats.png"); // TODO in manager

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

void MyRayLib::ShowPlayerData::setModel(const MyRayLib::Model &model) {
    this->_model = model.getModel();
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

int MyRayLib::ShowPlayerData::getPlayerIndexSelected() {
    return this->_index;
}

int MyRayLib::ShowPlayerData::getNumberOfResource(ZappyGui::IResource::resourceType type, const std::unordered_map<ZappyGui::IResource::resourceType, int> &tmpInventory) {
    int value = 0;
    auto itemSearch = tmpInventory.find(type);

    if (itemSearch != tmpInventory.end()) {
        value = itemSearch->second;
    }
    return value;
}

void MyRayLib::ShowPlayerData::ShowDataForEachPlayer(std::vector<std::shared_ptr<ZappyGui::Player>> _players)
{
    std::string tmpStr;
    this->_posX = 30.0;
    this->_posY = 60.0;
    float resourceX = 20;
    float resourceY = 900;
    if (_players.size() == 0)
        return;
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_PAGE_DOWN)) {
        if (this->_index >= (_players.size() - 1))
            this->_index = 0;
        else
            this->_index++;
    }
    if (IsKeyPressed(KEY_PAGE_UP)) {
        if (this->_index <= 0)
            this->_index = _players.size() - 1;
        else
            this->_index--;
    }

    for (size_t i = 0; i < _players.size(); ++i) {
        if (i == this->_index) {
            DrawText(std::to_string(_players.at(i)->getPlayerNumber()).c_str(), this->_posX, this->_posY, 20, ORANGE);
            DrawTexture(this->_texture, resourceX, resourceY, WHITE);
            DrawText(std::to_string(_players.at(i)->getPlayerLevel()).c_str(), resourceX += 75, resourceY += 20, 35, BLACK);
            DrawText((_players.at(i)->getTeamName()).c_str(), resourceX + 115, resourceY, 25, BLACK);
            const auto &tmpInventory = _players.at(i)->getInventory();
            int tmp = 0;

            resourceX -= 10;
            tmpStr = "x" + std::to_string(this->getNumberOfResource(ZappyGui::IResource::resourceType::BURGER, tmpInventory));
            DrawText(tmpStr.c_str(), resourceX, resourceY += 48, 25, BLACK);
            tmpStr = "x" + std::to_string(this->getNumberOfResource(ZappyGui::IResource::resourceType::DERAUMERE, tmpInventory));
            DrawText(tmpStr.c_str(), resourceX, resourceY += 54, 25, BLACK);
            resourceX += 125;
            resourceY -= 102;
            tmpStr = "x" + std::to_string(this->getNumberOfResource(ZappyGui::IResource::resourceType::LINEMATE, tmpInventory));
            DrawText(tmpStr.c_str(), resourceX, resourceY += 48, 25, BLACK);
            tmpStr = "x" + std::to_string(this->getNumberOfResource(ZappyGui::IResource::resourceType::MENDIANE, tmpInventory));
            DrawText(tmpStr.c_str(), resourceX, resourceY += 54, 25, BLACK);
            resourceX += 120;
            resourceY -= 102;
            tmpStr = "x" + std::to_string(this->getNumberOfResource(ZappyGui::IResource::resourceType::PHIRAS, tmpInventory));
            DrawText(tmpStr.c_str(), resourceX, resourceY += 48, 25, BLACK);
            tmpStr = "x" + std::to_string(this->getNumberOfResource(ZappyGui::IResource::resourceType::SIBUR, tmpInventory));
            DrawText(tmpStr.c_str(), resourceX, resourceY += 54, 25, BLACK);
            tmpStr = "x" + std::to_string(this->getNumberOfResource(ZappyGui::IResource::resourceType::THYSTAME, tmpInventory));
            DrawText(tmpStr.c_str(), resourceX += 115, resourceY -= 54, 25, BLACK);
        } else
            DrawText(std::to_string(_players.at(i)->getPlayerNumber()).c_str(), this->_posX, this->_posY, 20, BLACK);
        if (this->_posY >= 750) {
            this->_posY = 60.0;
            this->_posX += 60.0;
        } else
            this->_posY += 60.0;
    }
}
