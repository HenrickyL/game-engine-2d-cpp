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
    {VK_TAB, TAB},
    {VK_RETURN, ENTER},
    {0x41, KEY_A},
    {0x42, KEY_B},
    {0x44, KEY_D},
    {0x45, KEY_E},
    {0x46, KEY_F},
    {0x47, KEY_G},
    {0x48, KEY_H},
    {0x49, KEY_I},
    {0x4A, KEY_J},
    {0x4B, KEY_K},
    {0x4C, KEY_L},
    {0x4E, KEY_N},
    {0x4F, KEY_O},
    {0x50, KEY_P},
    {0x51, KEY_Q},
    {0x53, KEY_S},
    {0x54, KEY_T},
    {0x55, KEY_U},
    {0x56, KEY_V},
    {0x57, KEY_W},
    {0x58, KEY_X},
    {0x59, KEY_Y},
    {0x5A, KEY_Z},
    {VK_LSHIFT, LEFT_SHIFT},
    {VK_RSHIFT, RIGHT_SHIFT},
    {VK_LCONTROL, LEFT_CONTROL},
    {VK_RCONTROL, RIGHT_CONTROL},
};

#endif 
