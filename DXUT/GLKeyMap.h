#ifndef DXUT_GLKEYMAP_H
#define DXUT_GLKEYMAP_H

#include <unordered_map>
#include "InputKeys.h"
#include "GLIncludes.h"

std::unordered_map<int, InputKeys> GLKeyMap = { // Definição
    {GLFW_KEY_SPACE, SPACE},
    {GLFW_KEY_BACKSPACE, BACKSPACE},
    {GLFW_KEY_PAUSE, PAUSE},
    {GLFW_KEY_ESCAPE, ESCAPE},
    {GLFW_KEY_LEFT, LEFT},
    {GLFW_KEY_RIGHT, RIGHT},
    {GLFW_KEY_UP, UP},
    {GLFW_KEY_DOWN, DOWN},
    {GLFW_KEY_A, KEY_A},
    {GLFW_KEY_W, KEY_W},
    {GLFW_KEY_S, KEY_S},
    {GLFW_KEY_D, KEY_D},
    {GLFW_KEY_G, KEY_G},
    {GLFW_KEY_L, KEY_L},
    {GLFW_KEY_T, KEY_T},
    {GLFW_KEY_F, KEY_F},
};

#endif 
