/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** ShowPlayerData.cpp
*/

#include "../../includes/MapHeader/ShowPlayerData.hpp"

using namespace MyRayLib;
using namespace ZappyGui;

MyRayLib::ShowPlayerData::ShowPlayerData(ZappyGui::ServerLink &link) : _link(link)
{
    this->_image = LoadImage("./gui/assets/player_stats.png"); // TODO in manager

    this->_font = LoadFont("./Dongle-Bold.ttf");

    MyRayLib::Draw::MyImageDrawTextEx(&this->_image, this->_font, "PARROTS & CAT", (Vector2){ 300, 230 }, (float)this->_font.baseSize, -2, WHITE);

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

void MyRayLib::ShowPlayerData::drawInventory(int resourceX, int resourceY, const std::unordered_map<ZappyGui::IResource::resourceType, int>& inventory, const std::vector<ZappyGui::IResource::resourceType>& resourceTypes) {
    float originalResourceX = resourceX;
    float originalResourceY = resourceY;
    bool isAltLine = false;

    for (const auto& type : resourceTypes) {
        std::string tmpStr = "x" + std::to_string(this->getNumberOfResource(type, inventory));
        MyRayLib::Draw::MyDrawText(tmpStr.c_str(), resourceX, resourceY += 48, 25, BLACK);

        if (isAltLine) {
            resourceX += 125;
            resourceY = originalResourceY;
            isAltLine = false;  // reset for next line
        } else {
            isAltLine = true;
        }
    }

    resourceX = originalResourceX;
    resourceY += 102;
}

void MyRayLib::ShowPlayerData::ShowDataForEachPlayer(std::vector<std::shared_ptr<ZappyGui::Player>> playersList)
{
    std::vector<ZappyGui::IResource::resourceType> resourceTypes = {
        ZappyGui::IResource::resourceType::BURGER,
        ZappyGui::IResource::resourceType::DERAUMERE,
        ZappyGui::IResource::resourceType::LINEMATE,
        ZappyGui::IResource::resourceType::MENDIANE,
        ZappyGui::IResource::resourceType::PHIRAS,
        ZappyGui::IResource::resourceType::SIBUR,
        ZappyGui::IResource::resourceType::THYSTAME
    };

    this->_posX = 30.0;
    this->_posY = 60.0;
    if (playersList.empty())
        return;
    if (MyRayLib::MyRayLibWindow::MyIsKeyPressed(KEY_ENTER) || MyRayLib::MyRayLibWindow::MyIsKeyPressed(KEY_PAGE_DOWN)) {
        this->_index = (this->_index >= (playersList.size() - 1)) ? 0 : this->_index + 1;
        this->_link.askPlayerInventory(this->_index);
    }
    if (MyRayLib::MyRayLibWindow::MyIsKeyPressed(KEY_PAGE_UP)) {
        this->_index = (this->_index <= 0) ? playersList.size() - 1 : this->_index - 1;
        this->_link.askPlayerInventory(this->_index);
    }
    for (size_t i = 0; i < playersList.size(); ++i) {
        auto player = playersList[i];
        auto playerNumber = std::to_string(player->getPlayerNumber()).c_str();
        const std::unordered_map<ZappyGui::IResource::resourceType, int> &tmpInventory = player->getInventory();

        if (i == this->_index) {
            float resourceX = 20;
            float resourceY = 910;
            MyRayLib::Draw::MyDrawText(playerNumber, this->_posX, this->_posY, 20, ORANGE);
            MyRayLib::Draw::MyDrawTexture(this->_texture, resourceX, resourceY, WHITE);
            MyRayLib::Draw::MyDrawText(std::to_string(player->getPlayerLevel()).c_str(), resourceX += 75, resourceY += 20, 35, BLACK);
            MyRayLib::Draw::MyDrawText((player->getTeamName()).c_str(), resourceX + 115, resourceY, 25, BLACK);

            resourceX -= 10;
            drawInventory(resourceX, resourceY, tmpInventory, resourceTypes);
        } else {
            MyRayLib::Draw::MyDrawText(playerNumber, this->_posX, this->_posY, 20, BLACK);
        }

        if (this->_posY >= 750) {
            this->_posY = 60.0;
            this->_posX += 60.0;
        } else {
            this->_posY += 60.0;
        }
    }
}

