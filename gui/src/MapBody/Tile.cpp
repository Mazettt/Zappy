#include <random>
#include <algorithm>
#include "../../includes/MapHeader/Tile.hpp"

using namespace ZappyGui;

Tile::Tile(const Cube &cube): _cube(cube) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            _availablePositions.push_back({i, j});
        }
    }
}

void Tile::addResource(const ResourceManager &manager, IResource::resourceType type) {
    float decalage = -0.42;

    if (_availablePositions.empty()) {
        return;
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(_availablePositions.begin(), _availablePositions.end(), g);

    auto [x_index, z_index] = _availablePositions.back();
    _availablePositions.pop_back();
    float x_pos = decalage + x_index * 0.12;
    float z_pos = decalage + z_index * 0.12;
    this->_resources.push_back(FactoryResource::createResource(type, {x_pos + this->_cube.getPos().getX(), 0.0, z_pos + this->_cube.getPos().getZ()}, manager, -1));
}

void Tile::addEgg(const ResourceManager &manager, int id) {
    float decalage = -0.42;

    if (_availablePositions.empty()) {
        return;
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(_availablePositions.begin(), _availablePositions.end(), g);

    auto [x_index, z_index] = _availablePositions.back();
    _availablePositions.pop_back();
    float x_pos = decalage + x_index * 0.12;
    float z_pos = decalage + z_index * 0.12;
    this->_resources.push_back(FactoryResource::createResource(IResource::resourceType::EGG, {x_pos + this->_cube.getPos().getX(), 0.0, z_pos + this->_cube.getPos().getZ()}, manager, id));
}

void Tile::removeResource(const IResource::resourceType type) {
    float decalage = -0.42;
    auto it = std::find_if(this->_resources.begin(), this->_resources.end(),
        [type](const auto& resource) {
            return resource->getType() == type;
        }
    );
    if (it != this->_resources.end()) {
        float x_pos_without_cube = it->get()->getPosition().getX() - this->_cube.getPos().getX();
        float z_pos_without_cube = it->get()->getPosition().getZ() - this->_cube.getPos().getZ();

        int x_index = static_cast<int>(round((x_pos_without_cube - decalage) / 0.12));
        int z_index = static_cast<int>(round((z_pos_without_cube - decalage) / 0.12));
        _availablePositions.push_back({ x_index, z_index});
        this->_resources.erase(it);
    }
}

void Tile::removeEgg(int id) {
    float decalage = -0.42;
    auto it = std::find_if(this->_resources.begin(), this->_resources.end(),
        [id](const auto& resource) {
            return resource->getId() == id;
        }
    );
    if (it != this->_resources.end()) {
        float x_pos_without_cube = it->get()->getPosition().getX() - this->_cube.getPos().getX();
        float z_pos_without_cube = it->get()->getPosition().getZ() - this->_cube.getPos().getZ();

        int x_index = static_cast<int>(round((x_pos_without_cube - decalage) / 0.12));
        int z_index = static_cast<int>(round((z_pos_without_cube - decalage) / 0.12));
        _availablePositions.push_back({ x_index, z_index});
        this->_resources.erase(it);
    }
}

int Tile::countSpecificResource(IResource::resourceType type) {
    int counter = 0;
    int nbrResource = this->_resources.size();

    for (int i = 0; i < nbrResource; ++i) {
        if (this->_resources.at(i)->getType() == type) {
            counter += 1;
        }
    }
    return counter;
}

void Tile::drawContentPopup(const MyRayLib::Texture2D &texture, int nbrPlayer) {
    int x = 1750;
    int y = 348;
    std::vector<IResource::resourceType> resourceTypes = {
        IResource::resourceType::BURGER,
        IResource::resourceType::DERAUMERE,
        IResource::resourceType::LINEMATE,
        IResource::resourceType::MENDIANE,
        IResource::resourceType::PHIRAS,
        IResource::resourceType::SIBUR,
        IResource::resourceType::THYSTAME
    };

    MyRayLib::Draw::MyDrawTexture(texture.getTexture(), 1750, y, WHITE);
    x += 70;
    MyRayLib::Draw::MyDrawText(std::to_string(static_cast<int>(this->_cube.getPos().getX())).c_str(), x, y += 16, 25, BLACK);
    MyRayLib::Draw::MyDrawText(std::to_string(static_cast<int>(this->_cube.getPos().getZ())).c_str(), x, (y += 30) + 4, 25, BLACK);

    std::string tmp = "x" + std::to_string(nbrPlayer);
    MyRayLib::Draw::MyDrawText(tmp.c_str(), x, y += 50, 30, BLACK);
    for (const auto &type : resourceTypes) {
        std::string tmp = "x" + std::to_string(this->countSpecificResource(type));
        MyRayLib::Draw::MyDrawText(tmp.c_str(), x, y += 50, 30, BLACK);
    }
}

void Tile::draw() {
    this->_cube.draw();

    int nbrResource = this->_resources.size();
    for (int i = 0; i < nbrResource; ++i) {
        this->_resources.at(i)->draw();
    }
}

Tile::~Tile() {}
