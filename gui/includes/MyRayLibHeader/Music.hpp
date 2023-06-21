/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** Music.hpp
*/

#pragma once

#include <iostream>
#include "raylib.h"

namespace MyRayLib {
    class Music {
        private:
            ::Music _music;
        public:
            Music(const std::string &path) {
                _music = LoadMusicStream(path.c_str());
            }
            ~Music() {
                UnloadMusicStream(_music);
            }
            bool MyIsMusicReady() {
                return IsMusicReady(_music);
            }
            void MyUpdateMusic() {
                UpdateMusicStream(_music);
            }
            void MyPlayMusic() {
                PlayMusicStream(_music);
            }
            void MyStopMusic() {
                StopMusicStream(_music);
            }
            void MyPauseMusic() {
                PauseMusicStream(_music);
            }
            void MyResumeMusic() {
                ResumeMusicStream(_music);
            }
            bool MyIsMusicPlaying() {
                return IsMusicStreamPlaying(_music);
            }
            void MySetMusicVolume(float volume) {
                SetMusicVolume(_music, volume);
            }
            void MyLoadMusic(const std::string &filename) {
                UnloadMusicStream(this->_music);
                this->_music = LoadMusicStream(filename.c_str());
            }
            float MyGetMusicTimeLength() {
                return GetMusicTimeLength(_music);
            }
            float MyGetMusicTimePlayed() {
                return GetMusicTimePlayed(_music);
            }
    };
}
