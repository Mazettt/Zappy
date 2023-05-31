/*
** EPITECH PROJECT, 2022
** gui
** File description:
** FactoryResource.hpp
*/

#pragma once
#include <string>
#include <memory>
#include "IResource.hpp"
#include "Resources.hpp"

namespace ZappyGui {
    class FactoryResource {
        private:
            /* data */
        public:
            FactoryResource(std::string type);
            std::unique_ptr<IResource> createResource(const std::string &type);
            ~FactoryResource();
    };
}
