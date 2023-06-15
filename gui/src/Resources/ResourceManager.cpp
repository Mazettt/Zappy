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
    // // load player
    this->loadModel(IResource::resourceType::PLAYER, "./gui/assets/thegarfrotated.iqm");
    this->loadTexture(IResource::resourceType::PLAYER, "./gui/assets/T_Garfield_BC.png");
    this->loadAnimation(IResource::resourceType::PLAYER, "./gui/assets/thegarfrotated.iqm");
    this->loadModel(IResource::resourceType::PLAYER_SELECTOR, "./gui/assets/player_selector.iqm");
    this->loadTexture(IResource::resourceType::PLAYER_SELECTOR, "./gui/assets/player_selector.png");
    this->loadAnimation(IResource::resourceType::PLAYER_SELECTOR, "./gui/assets/player_selector.iqm");

    // // load texture
    this->loadModel(IResource::resourceType::DERAUMERE, "./gui/assets/Stones/stone_model.obj");
    this->loadModel(IResource::resourceType::LINEMATE, "./gui/assets/Stones/stone_model.obj");
    this->loadModel(IResource::resourceType::MENDIANE, "./gui/assets/Stones/stone_model.obj");
    this->loadModel(IResource::resourceType::PHIRAS, "./gui/assets/Stones/stone_model.obj");
    this->loadModel(IResource::resourceType::SIBUR, "./gui/assets/Stones/stone_model.obj");
    this->loadModel(IResource::resourceType::THYSTAME, "./gui/assets/Stones/stone_model.obj");

    this->loadTexture(IResource::resourceType::DERAUMERE, "./gui/assets/Stones/deraumere.png");
    this->loadTexture(IResource::resourceType::LINEMATE, "./gui/assets/Stones/linemate.png");
    this->loadTexture(IResource::resourceType::MENDIANE, "./gui/assets/Stones/mendiane.png");
    this->loadTexture(IResource::resourceType::PHIRAS, "./gui/assets/Stones/phiras.png");
    this->loadTexture(IResource::resourceType::SIBUR, "./gui/assets/Stones/sibur.png");
    this->loadTexture(IResource::resourceType::THYSTAME, "./gui/assets/Stones/thystame.png");

    this->loadTexture(IResource::resourceType::LOGO, "./gui/assets/logo.png");
    this->loadTexture(IResource::resourceType::BUTTON_START, "./gui/assets/Buttons/buttonStart.png");
    this->loadTexture(IResource::resourceType::BUTTON_HELP, "./gui/assets/Buttons/buttonHelp.png");
    this->loadTexture(IResource::resourceType::BUTTON_QUIT, "./gui/assets/Buttons/buttonQuit.png");

    this->loadTexture(IResource::resourceType::POPUP, "./gui/assets/popup.png");
    this->loadTexture(IResource::resourceType::POPUPTILE, "./gui/assets/tileInventory.png");

    // load food
    this->loadModel(IResource::resourceType::BURGER, "./gui/assets/Food/Hamburger.obj");
    this->loadTexture(IResource::resourceType::BURGER, "./gui/assets/Food/Hamburger.png");

    //load egg
    this->loadModel(IResource::resourceType::EGG, "./gui/assets/Egg/egg01.obj");
    this->loadTexture(IResource::resourceType::EGG, "./gui/assets/Egg/egg01.png");

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
    this->setMaterialTexture(IResource::resourceType::PLAYER_SELECTOR);
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

MyRayLib::Model &ResourceManager::getNoneConstModel(IResource::resourceType type) {
    if (_models.find(type) == _models.end())
        throw std::runtime_error("Model not loaded: " + type);
    return *_models.at(type);
}

const MyRayLib::Texture2D &ResourceManager::getTexture(IResource::resourceType type) const {
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
