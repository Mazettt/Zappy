/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** ShowPlayerData.hpp
*/

#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Player.hpp"
#include "../Server/ServerLink.hpp"

namespace MyRayLib {
    class ShowPlayerData {
        private:
            ::Image _image;
            ::Font _font;
            ::Texture2D _texture;
            float _posX;
            float _posY;
            size_t _index;
            ::Model _model;
            void drawInventory(int resourceX, int resourceY, const std::unordered_map<ZappyGui::IResource::resourceType, int>& inventory, const std::vector<ZappyGui::IResource::resourceType>& resourceTypes);
            ZappyGui::ServerLink &_link;
        public:
            ShowPlayerData(ZappyGui::ServerLink &link);
            ~ShowPlayerData();
            void setModel(const MyRayLib::Model &model);
            int getPlayerIndexSelected();
            void ShowDataForEachPlayer(std::vector<std::shared_ptr<ZappyGui::Player>> _players);
            std::string getRessourceName(ZappyGui::IResource::resourceType type);
            int getNumberOfResource(ZappyGui::IResource::resourceType type, const std::unordered_map<ZappyGui::IResource::resourceType, int> &tmpInventory);
        };
}
