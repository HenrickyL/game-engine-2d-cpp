#ifndef DXUT_GLKEYMAP_H
#define DXUT_GLKEYMAP_H

#include <unordered_map>
#include "InputKeys.h"
#include <GLFW/glfw3.h>

std::unordered_map<InputKeys, int> GLKeyMap = { // Definição
    {SPACE, GLFW_KEY_SPACE},
};

#endif 
