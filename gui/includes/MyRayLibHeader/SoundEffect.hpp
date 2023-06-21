/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Sound.hpp
*/

#pragma once

#include "raylib.h"
#include <string>

namespace MyRayLib {
    class SoundEffect {
    private:
        ::Sound _sound;

    public:
        SoundEffect(const std::string& filePath) {
            this->_sound = LoadSound(filePath.c_str());
        }
        ~SoundEffect() {
            UnloadSound(this->_sound);
        }
        void play() const {
            PlaySound(this->_sound);
        }
        void stop() const {
            StopSound(this->_sound);
        }
        void setVolume(float volume) {
            SetSoundVolume(this->_sound, volume);
        }
        bool IsPlaying() {
            return IsSoundPlaying(this->_sound);
        }
    };
}
