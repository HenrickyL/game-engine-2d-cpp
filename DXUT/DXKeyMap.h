#ifndef DXUT_DXKEYMAP_H
#define DXUT_DXKEYMAP_H

#include <unordered_map>
#include "InputKeys.h"
#include <WinUser.h>

std::unordered_map<WPARAM, InputKeys> DXKeyMap = { // Definição
    {VK_SPACE, SPACE},
    {VK_ESCAPE, ESCAPE},
    //convert another
    {0x08, BACKSPACE},
    {VK_PAUSE, PAUSE},
    {VK_LEFT, LEFT},
    {VK_RIGHT, RIGHT},
    {VK_UP, UP},
    {VK_DOWN, DOWN},
    {0x52, KEY_R},
    {0x4D, KEY_M},
    {0x43, KEY_C},
};

#endif 
