/*
** EPITECH PROJECT, 2022
** gui
** File description:
** ResourceManager.hpp
*/

#pragma once
#include <mutex>
#include <string>
#include <memory>
#include <unordered_map>
#include "IResource.hpp"
#include "../MyRayLibHeader/SoundEffect.hpp"
#include "../MyRayLibHeader/Model.hpp"
#include "../MyRayLibHeader/Texture.hpp"
#include "../MyRayLibHeader/AnimationsModel.hpp"

namespace ZappyGui {
    class ResourceManager {
        public:
            enum soundEffectType {
                EFFECT_JOIN,
                EFFECT_LEAVE,
                EFFECT_CLICK,
                EFFECT_VICTORY
            };

        private:
            std::mutex _mtx;
            std::unordered_map<IResource::resourceType, std::unique_ptr<MyRayLib::Model>> _models;
            std::unordered_map<IResource::resourceType, std::unique_ptr<MyRayLib::Texture2D>> _textures;
            std::unordered_map<IResource::resourceType, std::unique_ptr<MyRayLib::AnimationsModel>> _animations;
            std::unordered_map<soundEffectType, std::unique_ptr<MyRayLib::SoundEffect>> _soundsEffect;

        public:
            bool _isLoaded;
            ResourceManager();
            ~ResourceManager();
            void loadModel(IResource::resourceType type, const std::string &filename);
            void loadTexture(IResource::resourceType type, const std::string &filename);
            void loadAnimation(IResource::resourceType type, const std::string &filename);
            void loadSoundEffect(soundEffectType type, const std::string &filename);
            const MyRayLib::Model &getModel(IResource::resourceType type) const;
            const MyRayLib::Texture2D &getTexture(IResource::resourceType type) const;
            MyRayLib::SoundEffect &getSoundEffect(soundEffectType type);
            MyRayLib::AnimationsModel &getAnimation(IResource::resourceType type);
            void setMaterialTexture(IResource::resourceType type);
            MyRayLib::Model &getNoneConstModel(IResource::resourceType type);
            bool getIsLoaded();
            void initialize();
            void loadBasicResource();
    };
}
