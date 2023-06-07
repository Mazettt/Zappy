/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Button.hpp
*/

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <raylib.h>
#include <raymath.h>

typedef enum {
    CHROMA,
    CLOWN,
    DEGUEUVERT,
    FRAGMENT,
    GAUSSIAN,
    NIGHTVIS,
    PREDATOR
    
} ShaderType;

static const char *shaderNames[] = {
    "chroma",
    "clown",
    "degueuvert",
    "fragment",
    "gaussian",
    "nightvis",
    "predator"
};
