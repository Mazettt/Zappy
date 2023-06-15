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
    static const std::unordered_map<IResource::resourceType, std::function<std::unique_ptr<IResource>(const Vector3 &, const ResourceManager &)>> componentMap {
        {IResource::resourceType::BURGER, [](const Vector3 &position, const ResourceManager &manager)
            {return std::make_unique<Burger>(manager.getModel(IResource::resourceType::BURGER), manager.getTexture(IResource::resourceType::BURGER), position);}},
        {IResource::resourceType::LINEMATE, [](const Vector3 &position, const ResourceManager &manager)
            {return std::make_unique<Linemate>(manager.getModel(IResource::resourceType::LINEMATE), manager.getTexture(IResource::resourceType::LINEMATE), position);}},
        {IResource::resourceType::DERAUMERE, [](const Vector3 &position, const ResourceManager &manager)
            {return std::make_unique<Deraumere>(manager.getModel(IResource::resourceType::DERAUMERE), manager.getTexture(IResource::resourceType::DERAUMERE), position);}},
        {IResource::resourceType::SIBUR, [](const Vector3 &position, const ResourceManager &manager)
            {return std::make_unique<Sibur>(manager.getModel(IResource::resourceType::SIBUR), manager.getTexture(IResource::resourceType::SIBUR), position);}},
        {IResource::resourceType::MENDIANE, [](const Vector3 &position, const ResourceManager &manager)
            {return std::make_unique<Mendiane>(manager.getModel(IResource::resourceType::MENDIANE), manager.getTexture(IResource::resourceType::MENDIANE), position);}},
        {IResource::resourceType::PHIRAS, [](const Vector3 &position, const ResourceManager &manager)
            {return std::make_unique<Phiras>(manager.getModel(IResource::resourceType::PHIRAS), manager.getTexture(IResource::resourceType::PHIRAS), position);}},
        {IResource::resourceType::THYSTAME, [](const Vector3 &position, const ResourceManager &manager)
            {return std::make_unique<Thystame>(manager.getModel(IResource::resourceType::THYSTAME), manager.getTexture(IResource::resourceType::THYSTAME), position);}},
        {IResource::resourceType::EGG, [](const Vector3 &position, const ResourceManager &manager)
            {return std::make_unique<Egg>(manager.getModel(IResource::resourceType::EGG), manager.getTexture(IResource::resourceType::EGG), position);}}
    };
    auto it = componentMap.find(type);
    if (it == componentMap.end())
        throw std::out_of_range(std::string("Unknown resource type: ") + std::to_string(type));

    return it->second(position, manager);
}
