/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** Model.hpp
*/

#pragma once

#include <iostream>
#include "raylib.h"

namespace MyRayLib {
    class Model {
        private:
            ::Model _model;
        public:
            Model(const std::string &path){
                _model = LoadModel(path.c_str());
            }
            Model(const ::Model &other) {
                this->_model = other;
            }
            ~Model() {
                UnloadModel(_model);
            }
            const ::Model getModel() const {
                return _model;
            }
            void operator=(const ::Model &model) {
                _model = model;
            }
    };
}
