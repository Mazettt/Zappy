/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** MyError.cpp
*/

#include "MyError.hpp"

ZappyAI::MyError::MyError(std::string const &message) : _message(message)
{
    std::cerr << _message << std::endl;
}

const char *ZappyAI::MyError::what() const noexcept
{
    return _message.c_str();
}