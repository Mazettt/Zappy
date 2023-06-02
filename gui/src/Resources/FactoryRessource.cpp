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
    this->loadEveryResources();
}

FactoryResource::~FactoryResource() {}

std::unique_ptr<IResource> FactoryResource::createResource(const std::string &type) {
    static const std::unordered_map<std::string, std::function<std::unique_ptr<IResource>()>> componentMap {
        {"food", []() {return std::make_unique<Food>();}},
        {"linemate", []() {return std::make_unique<Linemate>();}},
        {"deraumere", []() {return std::make_unique<Deraumere>();}},
        {"sibur", []() {return std::make_unique<Sibur>();}},
        {"mendiane", []() {return std::make_unique<Mendiane>();}},
        {"phiras", []() {return std::make_unique<Phiras>();}},
        {"thystame", []() {return std::make_unique<Thystame>();}}
    };
    std::unordered_map<std::string, std::function<std::unique_ptr<IResource>()>>::const_iterator it = componentMap.find(type);
    if (it == componentMap.end())
        throw std::out_of_range("Unknown resource type: " + type);
    return it->second();
}

std::unique_ptr<IResource> FactoryResource::createResource(int type) {
    static const std::unordered_map<int, std::function<std::unique_ptr<IResource>()>> componentMap {
        {0, []() {return std::make_unique<Food>();}},
        {1, []() {return std::make_unique<Linemate>();}},
        {2, []() {return std::make_unique<Deraumere>();}},
        {3, []() {return std::make_unique<Sibur>();}},
        {4, []() {return std::make_unique<Mendiane>();}},
        {5, []() {return std::make_unique<Phiras>();}},
        {6, []() {return std::make_unique<Thystame>();}}
    };
    std::unordered_map<int, std::function<std::unique_ptr<IResource>()>>::const_iterator it = componentMap.find(type);
    if (it == componentMap.end())
        throw std::out_of_range("Unknown resource type: " + type);
    return it->second();
}

std::unique_ptr<IResource> FactoryResource::createResourceTest(IResource::resourceType type) {
    static const std::unordered_map<int, std::function<std::unique_ptr<IResource>()>> componentMap {
        {IResource::resourceType::FOOD, []() {return std::make_unique<Food>();}},
        {IResource::resourceType::LINEMATE, []() {return std::make_unique<Linemate>();}},
        {IResource::resourceType::DERAUMERE, []() {return std::make_unique<Deraumere>();}},
        {IResource::resourceType::SIBUR, []() {return std::make_unique<Sibur>();}},
        {IResource::resourceType::MENDIANE, []() {return std::make_unique<Mendiane>();}},
        {IResource::resourceType::PHIRAS, []() {return std::make_unique<Phiras>();}},
        {IResource::resourceType::THYSTAME, []() {return std::make_unique<Thystame>();}}
    };
    std::unordered_map<int, std::function<std::unique_ptr<IResource>()>>::const_iterator it = componentMap.find(type);
    if (it == componentMap.end())
        throw std::out_of_range("Unknown resource type: " + type);
    return it->second();
}

void FactoryResource::loadEveryResources() {
    for (int i = 0; i < 7; ++i) {
        _resourceMap.insert({(IResource::resourceType)i, this->createResourceTest((IResource::resourceType)i)});
    }
}

const std::map<IResource::resourceType, std::unique_ptr<IResource>> &FactoryResource::getResourceMap() const {
    return this->_resourceMap;
}
