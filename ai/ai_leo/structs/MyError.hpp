/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** MyError.hpp
*/

#pragma once

#include <exception>
#include <string>
#include <iostream>

namespace ZappyAI {
    class MyError : public std::exception {
        public:
            MyError(std::string const &message);
            ~MyError() = default;
            const char *what() const noexcept override;
        private:
            std::string _message;
    };
};