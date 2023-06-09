/*
** EPITECH PROJECT, 2022
** gui
** File description:
** ResourceManager.cpp
*/

#include "../../includes/resources/ResourceManager.hpp"
using namespace ZappyGui;

ResourceManager::ResourceManager() {

}

ResourceManager::~ResourceManager() {
    _models.clear();
    _textures.clear();
    _animations.clear();
}

void ResourceManager::initialize() {
    this->loadTexture(IResource::resourceType::PARALLAX_MENU_BACKGROUND, "./assets/Parallax/bkgParallax.png");
    this->loadTexture(IResource::resourceType::PARALLAX_MENU_MIDDLE, "./assets/Parallax/garfTerre.png");
    // // load player
    this->loadModel(IResource::resourceType::PLAYER, "./assets/thegarfrotated.iqm");
    this->loadTexture(IResource::resourceType::PLAYER, "./assets/T_Garfield_BC.png");
    this->loadAnimation(IResource::resourceType::PLAYER, "./assets/thegarfrotated.iqm");

    // // load texture
    this->loadModel(IResource::resourceType::DERAUMERE, "./assets/Stones/stone_model.obj");
    this->loadModel(IResource::resourceType::LINEMATE, "./assets/Stones/stone_model.obj");
    this->loadModel(IResource::resourceType::MENDIANE, "./assets/Stones/stone_model.obj");
    this->loadModel(IResource::resourceType::PHIRAS, "./assets/Stones/stone_model.obj");
    this->loadModel(IResource::resourceType::SIBUR, "./assets/Stones/stone_model.obj");
    this->loadModel(IResource::resourceType::THYSTAME, "./assets/Stones/stone_model.obj");

    this->loadTexture(IResource::resourceType::DERAUMERE, "./assets/Stones/deraumere.png");
    this->loadTexture(IResource::resourceType::LINEMATE, "./assets/Stones/linemate.png");
    this->loadTexture(IResource::resourceType::MENDIANE, "./assets/Stones/mendiane.png");
    this->loadTexture(IResource::resourceType::PHIRAS, "./assets/Stones/phiras.png");
    this->loadTexture(IResource::resourceType::SIBUR, "./assets/Stones/sibur.png");
    this->loadTexture(IResource::resourceType::THYSTAME, "./assets/Stones/thystame.png");

    this->loadTexture(IResource::resourceType::BUTTON_START, "./assets/Buttons/buttonStart.png");
    this->loadTexture(IResource::resourceType::BUTTON_HELP, "./assets/Buttons/buttonHelp.png");
    this->loadTexture(IResource::resourceType::BUTTON_QUIT, "./assets/Buttons/buttonQuit.png");


    // load food
    this->loadModel(IResource::resourceType::BURGER, "./assets/Food/Hamburger.obj");
    this->loadTexture(IResource::resourceType::BURGER, "./assets/Food/Hamburger.png");

    //load egg
    this->loadModel(IResource::resourceType::EGG, "./assets/Egg/egg01.obj");
    this->loadTexture(IResource::resourceType::EGG, "./assets/Egg/egg01.png");

    // load texture on model
    this->setMaterialTexture(IResource::resourceType::DERAUMERE);
    this->setMaterialTexture(IResource::resourceType::LINEMATE);
    this->setMaterialTexture(IResource::resourceType::MENDIANE);
    this->setMaterialTexture(IResource::resourceType::PHIRAS);
    this->setMaterialTexture(IResource::resourceType::SIBUR);
    this->setMaterialTexture(IResource::resourceType::THYSTAME);
    this->setMaterialTexture(IResource::resourceType::BURGER);
    this->setMaterialTexture(IResource::resourceType::PLAYER);
    this->setMaterialTexture(IResource::resourceType::EGG);
}

void ResourceManager::loadModel(IResource::resourceType type, const std::string &filename) {
    if (_models.find(type) == _models.end())
        _models[type] = std::make_unique<MyRayLib::Model>(filename);
}

void ResourceManager::loadTexture(IResource::resourceType type, const std::string &filename) {
    if (_textures.find(type) == _textures.end())
        _textures[type] = std::make_unique<MyRayLib::Texture2D>(filename);
}

void ResourceManager::loadAnimation(IResource::resourceType type, const std::string &filename) {
    if (_animations.find(type) == _animations.end())
        _animations[type] = std::make_unique<MyRayLib::AnimationsModel>(filename);
}

const MyRayLib::Model &ResourceManager::getModel(IResource::resourceType type) const {
    if (_models.find(type) == _models.end())
        throw std::runtime_error("Model not loaded: " + type);
    return *_models.at(type);
}

MyRayLib::Model &ResourceManager::getPlayerModel() {
    if (_models.find(IResource::resourceType::PLAYER) == _models.end())
        throw std::runtime_error("Model not loaded: " + IResource::resourceType::PLAYER);
    return *_models.at(IResource::resourceType::PLAYER);
}

const MyRayLib::Texture2D &ResourceManager::getTexture(IResource::resourceType type) const {
    std::cout << "type " << type << std::endl;
    if (_textures.find(type) == _textures.end())
        throw std::runtime_error("Texture not loaded: " + type);
    return *_textures.at(type);
}

MyRayLib::AnimationsModel &ResourceManager::getAnimation(IResource::resourceType type) {
    if (_animations.find(type) == _animations.end())
        throw std::runtime_error("Animation not loaded: " + type);
    return *_animations.at(type);
}

void ResourceManager::setMaterialTexture(IResource::resourceType type) {
    auto model_it = _models.find(type);
    auto texture_it = _textures.find(type);

    if(model_it == _models.end()) {
        throw std::runtime_error("Model not loaded: " + type);
    }
    if(texture_it == _textures.end()) {
        throw std::runtime_error("Texture not loaded: " + type);
    }
    texture_it->second->MySetMaterialTexture(model_it->second->getModel(), MATERIAL_MAP_DIFFUSE);
}
