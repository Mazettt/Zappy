/*
** EPITECH PROJECT, 2022
** gui
** File description:
** FactoryResource.cpp
*/

#include <functional>
#include <unordered_map>
#include "../../includes/resources/FactoryResource.hpp"

using namespace ZappyGui;

FactoryResource::FactoryResource() {
}

FactoryResource::~FactoryResource() {}

std::unique_ptr<IResource> FactoryResource::createResource(IResource::resourceType type, const Vector3 &position, const ResourceManager &manager) {
    static const std::unordered_map<IResource::resourceType, std::function<std::unique_ptr<IResource>()>> componentMap {
        {IResource::resourceType::PIZZA, [&]()
            {return std::make_unique<Pizza>(manager.getModel(type), manager.getTexture(type), position);}},
        {IResource::resourceType::LINEMATE, [&]()
            {return std::make_unique<Linemate>(manager.getModel(type), manager.getTexture(type), position);}},
        {IResource::resourceType::DERAUMERE, [&]()
            {return std::make_unique<Deraumere>(manager.getModel(type), manager.getTexture(type), position);}},
        {IResource::resourceType::SIBUR, [&]()
            {return std::make_unique<Sibur>(manager.getModel(type), manager.getTexture(type), position);}},
        {IResource::resourceType::MENDIANE, [&]()
            {return std::make_unique<Mendiane>(manager.getModel(type), manager.getTexture(type), position);}},
        {IResource::resourceType::PHIRAS, [&]()
            {return std::make_unique<Phiras>(manager.getModel(type), manager.getTexture(type), position);}},
        {IResource::resourceType::THYSTAME, [&]()
            {return std::make_unique<Thystame>(manager.getModel(type), manager.getTexture(type), position);}}
    };
    std::unordered_map<IResource::resourceType, std::function<std::unique_ptr<IResource>()>>::const_iterator it = componentMap.find(type);
    if (it == componentMap.end())
        throw std::out_of_range("Unknown resource type: " + type);

    return it->second();
}
