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

namespace MyRayLib {
    class ShowPlayerData {
        private:
            ::Image _image;
            ::Font _font;
            ::Texture2D _texture;
            float _posX;
            float _posY;
            size_t _index;
        public:
            ShowPlayerData();
            ~ShowPlayerData();
            void ShowDataForEachPlayer(std::vector<std::shared_ptr<ZappyGui::Player>> _players);
            std::string getRessourceName(ZappyGui::IResource::resourceType type);
        };
}
