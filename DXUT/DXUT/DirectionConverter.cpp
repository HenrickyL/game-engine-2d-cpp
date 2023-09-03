#include "DXUT_Utils_Direction_.h"

std::unordered_map<Direction, float>  DirectionConverter::DirectionToRadiansTable = 
{
            {N, 0.0f},
            {NE, 0.7853981634f}, // 45 graus em radianos
            {E, 1.570796327f},   // 90 graus em radianos
            {SE, 2.35619449f},    // 135 graus em radianos
            {S, 3.141592654f},    // 180 graus em radianos
            {SW, 3.926990817f},   // 225 graus em radianos
            {W, 4.71238898f},     // 270 graus em radianos
            {NW, 5.497787143f}    // 315 graus em radianos
};;


float DirectionConverter::GetRadians(Direction direction)
{
    auto it = DirectionToRadiansTable.find(direction);
    if (it != DirectionToRadiansTable.end())
    {
        return it->second;
    }
    return 0.0f; // Retorne 0 para uma direção desconhecida (N por padrão).
}



//{N, 0.0f},
//{ NE, M_PI / 4.0f },
//{ E, M_PI / 2.0f },
//{ SE, 3.0f * M_PI / 4.0f },
//{ S, M_PI },
//{ SW, 5.0f * M_PI / 4.0f },
//{ W, 3.0f * M_PI / 2.0f },
//{ NW, 7.0f * M_PI / 4.0f }