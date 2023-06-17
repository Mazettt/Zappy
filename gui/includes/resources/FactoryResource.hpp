/*
** EPITECH PROJECT, 2022
** gui
** File description:
** FactoryResource.hpp
*/

#pragma once
#include <string>
#include <memory>
#include <map>
#include "IResource.hpp"
#include "Resources.hpp"
#include "ResourceManager.hpp"
#include "../MyRayLibHeader/Model.hpp"

namespace ZappyGui {
    class FactoryResource {
        public:
            FactoryResource();
            ~FactoryResource();
            static std::unique_ptr<IResource> createResource(IResource::resourceType type, const MyRayLib::Vector3D &position, const ResourceManager &manager, int id);
    };
}
