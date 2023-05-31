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

FactoryResource::FactoryResource() {}

FactoryResource::~FactoryResource() {}

std::unique_ptr<IResource> FactoryResource::createResource(const std::string &type) {
    static const std::unordered_map<std::string, std::function<std::unique_ptr<IResource>()>> componentMap {
        {"food", []() {return std::make_unique<Food>("quoi.obj", "feur.png");}}
    };
    std::unordered_map<std::string, std::function<std::unique_ptr<IResource>()>>::const_iterator it = componentMap.find(type);
    if (it == componentMap.end())
        throw std::out_of_range("Unknown resource type: " + type);
    return it->second();
}
