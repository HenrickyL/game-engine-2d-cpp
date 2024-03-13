#include "Color.h"


// Inicialização das cores estáticas
const Color Color::BLACK(0.0f, 0.0f, 0.0f);
const Color Color::RED(1.0f, 0.0f, 0.0f);
const Color Color::BLUE(0.0f, 0.0f, 1.0f);
const Color Color::GREEN(0.0f, 1.0f, 0.0f);
const Color Color::YELLOW(1.0f, 1.0f, 0.0f);
const Color Color::WHITE(1.0f, 1.0f, 1.0f);
const Color Color::MAGENTA(1.0f, 0.0f, 1.0f);
const Color Color::_TRANSPARENT(0.0f, 0.0f, 0.0f, 0.0f);

Color Color::modify(float luminosity) const {
    float modifiedR = std::round(_r * luminosity);
    float modifiedG = std::round(_g * luminosity);
    float modifiedB = std::round(_b * luminosity);

    // Garantir que os valores modificados estejam dentro do intervalo [0, 255]
    modifiedR = std::max(0.0f, std::min(255.0f, modifiedR));
    modifiedG = std::max(0.0f, std::min(255.0f, modifiedG));
    modifiedB = std::max(0.0f, std::min(255.0f, modifiedB));

    return Color(modifiedR, modifiedG, modifiedB, _a);
}
Color Color::interpolate(const Color& otherColor, float t) const {
    // Interpolação linear entre as cores
    float interpolatedR = (1 - t) * _r + t * otherColor._r;
    float interpolatedG = (1 - t) * _g + t * otherColor._g;
    float interpolatedB = (1 - t) * _b + t * otherColor._b;
    float interpolatedA = (1 - t) * _a + t * otherColor._a;

    return Color(interpolatedR, interpolatedG, interpolatedB, interpolatedA);
}

