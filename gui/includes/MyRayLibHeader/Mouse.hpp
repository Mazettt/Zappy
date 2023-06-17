/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Mouse.hpp
*/

#pragma once
#include <raylib.h>

namespace MyRayLib {
    class Mouse {
        public:
            Mouse() {};
            ~Mouse() {};
            static bool MyIsMouseButtonPressed(int button) {
                return ::IsMouseButtonPressed(button);
            }
            static Vector2 MyGetMousePosition() {
                return ::GetMousePosition();
            }
            static Ray MyGetMouseRay(::Vector2 mousePosition, const ::Camera &camera) {
                return ::GetMouseRay(mousePosition, camera);
            }
    };
}
