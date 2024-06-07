#include "Color.h"
#include <random>

// Inicialização das cores estáticas
const Color Color::BLACK(0.0f, 0.0f, 0.0f);
const Color Color::RED(1.0f, 0.0f, 0.0f);
const Color Color::BLUE(0.0f, 0.0f, 1.0f);
const Color Color::GREEN(0.0f, 1.0f, 0.0f);
const Color Color::YELLOW(1.0f, 1.0f, 0.0f);
const Color Color::WHITE(1.0f, 1.0f, 1.0f);
const Color Color::GRAY(0.4f, 0.4f, 0.4f);
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

Color Color::Brightness(float factor) const {
    float newR = _r * factor;
    float newG = _g * factor;
    float newB = _b * factor;

    // Ensure RGB values remain in the range [0, 1]
    newR = std::max(0.0f, std::min(1.0f, newR));
    newG = std::max(0.0f, std::min(1.0f, newG));
    newB = std::max(0.0f, std::min(1.0f, newB));

    return Color(newR, newG, newB, _a);

    //// Ajuste do fator de contraste
    //float value = 127.0f;
    //float contrastFactor = (factor + value) / value;

    //// Ajustar o contraste para cada componente de cor
    //float newR = contrastFactor * (_r - 0.5f) + 0.5f;
    //float newG = contrastFactor * (_g - 0.5f) + 0.5f;
    //float newB = contrastFactor * (_b - 0.5f) + 0.5f;

    //// Garantir que os valores estejam no intervalo [0, 1]
    //newR = std::max(0.0f, std::min(1.0f, newR));
    //newG = std::max(0.0f, std::min(1.0f, newG));
    //newB = std::max(0.0f, std::min(1.0f, newB));

    //return Color(newR, newG, newB, _a);
}



Color Color::UlongToColor(ulong colorValue)
{
    ulong alpha = (colorValue >> 24) & 0xFF;
    ulong red = (colorValue >> 16) & 0xFF;
    ulong green = (colorValue >> 8) & 0xFF;
    ulong blue = colorValue & 0xFF;

    float alphaFloat = static_cast<float>(alpha) / 255.0f;
    float redFloat = static_cast<float>(red) / 255.0f;
    float greenFloat = static_cast<float>(green) / 255.0f;
    float blueFloat = static_cast<float>(blue) / 255.0f;

    return Color(alphaFloat, redFloat, greenFloat, blueFloat);
}

ulong Color::ColorToUlong(const Color& color)
{
    ulong alpha = static_cast<ulong>(color.alpha() * 255) & 0xFF;
    ulong red = static_cast<ulong>(color.r() * 255) & 0xFF;
    ulong green = static_cast<ulong>(color.g() * 255) & 0xFF;
    ulong blue = static_cast<ulong>(color.b() * 255) & 0xFF;

    return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

Color Color::RandomColor() {
    static std::random_device rd;  // Seed for the random number engine
    static std::mt19937 gen(rd()); // Mersenne Twister engine
    static std::uniform_real_distribution<> dis(0.0, 1.0); // Uniform distribution between 0.0 and 1.0

    float r = dis(gen);
    float g = dis(gen);
    float b = dis(gen);
    return Color(r, g, b);
}


const float* Color::c3f() const {
    static float c[3];
    c[0] = _r;
    c[1] = _g;
    c[2] = _b;
    return c;
}

const float* Color::c4f() const {
    static float c[4];
    c[0] = _r;
    c[1] = _g;
    c[2] = _b;
    c[3] = _a;
    return c;
}