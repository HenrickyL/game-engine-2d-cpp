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
    {GLFW_KEY_LEFT_SHIFT, SHIFT_LEFT},
    {GLFW_KEY_RIGHT_SHIFT, SHIFT_RIGHT},
    {GLFW_KEY_LEFT_CONTROL, CTRL_LEFT},
    {GLFW_KEY_RIGHT_CONTROL, CTRL_RIGHT},
    {GLFW_KEY_TAB, TAB},
    {GLFW_KEY_ENTER, ENTER},
    {GLFW_KEY_B, KEY_B},
    {GLFW_KEY_C, KEY_C},
    {GLFW_KEY_E, KEY_E},
    {GLFW_KEY_H, KEY_H},
    {GLFW_KEY_I, KEY_I},
    {GLFW_KEY_J, KEY_J},
    {GLFW_KEY_K, KEY_K},
    {GLFW_KEY_M, KEY_M},
    {GLFW_KEY_N, KEY_N},
    {GLFW_KEY_O, KEY_O},
    {GLFW_KEY_P, KEY_P},
    {GLFW_KEY_Q, KEY_Q},
    {GLFW_KEY_R, KEY_R},
    {GLFW_KEY_U, KEY_U},
    {GLFW_KEY_V, KEY_V},
    {GLFW_KEY_X, KEY_X},
    {GLFW_KEY_Y, KEY_Y},
    {GLFW_KEY_Z, KEY_Z},
};

#endif 
