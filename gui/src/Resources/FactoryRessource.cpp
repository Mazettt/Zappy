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

std::unique_ptr<IResource> FactoryResource::createResource(IResource::resourceType type, const MyRayLib::Vector3D &position, const ResourceManager &manager, int id) {
    static const std::unordered_map<IResource::resourceType, std::function<std::unique_ptr<IResource>(const MyRayLib::Vector3D &, const ResourceManager &, int)>> componentMap {
        {IResource::resourceType::BURGER, [](const MyRayLib::Vector3D &position, const ResourceManager &manager, __attribute__((unused)) int id)
            {return std::make_unique<Burger>(manager.getModel(IResource::resourceType::BURGER), manager.getTexture(IResource::resourceType::BURGER), position);}},
        {IResource::resourceType::LINEMATE, [](const MyRayLib::Vector3D &position, const ResourceManager &manager, __attribute__((unused)) int id)
            {return std::make_unique<Linemate>(manager.getModel(IResource::resourceType::LINEMATE), manager.getTexture(IResource::resourceType::LINEMATE), position);}},
        {IResource::resourceType::DERAUMERE, [](const MyRayLib::Vector3D &position, const ResourceManager &manager, __attribute__((unused)) int id)
            {return std::make_unique<Deraumere>(manager.getModel(IResource::resourceType::DERAUMERE), manager.getTexture(IResource::resourceType::DERAUMERE), position);}},
        {IResource::resourceType::SIBUR, [](const MyRayLib::Vector3D &position, const ResourceManager &manager, __attribute__((unused)) int id)
            {return std::make_unique<Sibur>(manager.getModel(IResource::resourceType::SIBUR), manager.getTexture(IResource::resourceType::SIBUR), position);}},
        {IResource::resourceType::MENDIANE, [](const MyRayLib::Vector3D &position, const ResourceManager &manager, __attribute__((unused)) int id)
            {return std::make_unique<Mendiane>(manager.getModel(IResource::resourceType::MENDIANE), manager.getTexture(IResource::resourceType::MENDIANE), position);}},
        {IResource::resourceType::PHIRAS, [](const MyRayLib::Vector3D &position, const ResourceManager &manager, __attribute__((unused)) int id)
            {return std::make_unique<Phiras>(manager.getModel(IResource::resourceType::PHIRAS), manager.getTexture(IResource::resourceType::PHIRAS), position);}},
        {IResource::resourceType::THYSTAME, [](const MyRayLib::Vector3D &position, const ResourceManager &manager, __attribute__((unused)) int id)
            {return std::make_unique<Thystame>(manager.getModel(IResource::resourceType::THYSTAME), manager.getTexture(IResource::resourceType::THYSTAME), position);}},
        {IResource::resourceType::EGG, [](const MyRayLib::Vector3D &position, const ResourceManager &manager, int id)
            {return std::make_unique<Egg>(manager.getModel(IResource::resourceType::EGG), manager.getTexture(IResource::resourceType::EGG), position, id);}},
        {IResource::resourceType::BROADCAST, [](const MyRayLib::Vector3D &position, const ResourceManager &manager, int id)
            {return std::make_unique<Broadcast>(manager.getModel(IResource::resourceType::BROADCAST), manager.getTexture(IResource::resourceType::BROADCAST), position, id);}}
    };
    auto it = componentMap.find(type);
    if (it == componentMap.end())
        throw std::out_of_range(std::string("Unknown resource type: ") + std::to_string(type));

    return it->second(position, manager, id);
}
