#ifndef DXUT_UTILS_DIRECTION_H
#define DXUT_UTILS_DIRECTION_H
// ---------------------------------------------------------------------------------

#include <unordered_map>
// ---------------------------------------------------------------------------------

enum Direction
{
    N,
    NE,
    E,
    SE,
    S,
    SW,
    W,
    NW
};

class DirectionConverter
{
public:
    static float GetRadians(Direction direction);

private:
    static std::unordered_map<Direction, float> DirectionToRadiansTable;
};

#endif