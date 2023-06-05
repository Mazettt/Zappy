/*
** EPITECH PROJECT, 2022
** gui
** File description:
** ResourceManager.hpp
*/

#include <string>
#include <memory>
#include <unordered_map>
#include "IResource.hpp"
#include "../MyRayLibHeader/Model.hpp"
#include "../MyRayLibHeader/Texture.hpp"
#include "../MyRayLibHeader/AnimationsModel.hpp"

namespace ZappyGui {
    class ResourceManager {
        private:
            std::unordered_map<IResource::resourceType, std::unique_ptr<MyRayLib::Model>> _models;
            std::unordered_map<IResource::resourceType, std::unique_ptr<MyRayLib::Texture2D>> _textures;
            std::unordered_map<IResource::resourceType, std::unique_ptr<MyRayLib::AnimationsModel>> _animations;

        public:
            ResourceManager();
            ~ResourceManager();
            void loadModel(IResource::resourceType type, const std::string &filename);
            void loadTexture(IResource::resourceType type, const std::string &filename);
            void loadAnimation(IResource::resourceType type, const std::string &filename);
            const MyRayLib::Model &getModel(IResource::resourceType type) const;
            const MyRayLib::Texture2D &getTexture(IResource::resourceType type) const;
            MyRayLib::AnimationsModel &getAnimation(IResource::resourceType type);
            void setMaterialTexture(IResource::resourceType type);
    };
}
