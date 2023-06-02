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

namespace ZappyGui {
    class FactoryResource {
        private:
            std::map<IResource::resourceType, std::unique_ptr<IResource>> _resourceMap;
        public:
            FactoryResource();
            ~FactoryResource();
            const std::map<IResource::resourceType, std::unique_ptr<IResource>> &getResourceMap() const;
            static std::unique_ptr<IResource> createResource(const std::string &type);
            static std::unique_ptr<IResource> createResourceTest(IResource::resourceType type);
            static std::unique_ptr<IResource> createResource(int type);
            void loadEveryResources();
    };
}
