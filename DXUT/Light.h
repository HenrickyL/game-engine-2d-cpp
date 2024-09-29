#ifndef UT_LIGHT_H
#define UT_LIGHT_H

#include "Movable.h"
#include "Colored.h"

enum LightType {
    AMBIENT, // Luz ambiente global
    POINT,   // Luz pontual
    DIRECTIONAL, // Luz direcional
    SPOTLIGHT // Luz tipo holofote
};


class Light : public Movable, public Colored {
protected:
    float _intensity;   // Intensidade da luz
    LightType _type;    // Tipo de luz

public:
    Light(const Vector& position, float intensity, LightType type);
    Light(const Color& color, float intensity, LightType type);
    Light(const Vector& position, const Color& color, float intensity, LightType type);


    float intensity() const;
    void SetIntensity(float intensity);
    LightType type() const;
    void SetType(LightType type);

    // virtual
    virtual void Enable() = 0;
    virtual void Disable() = 0;
    virtual void Update() = 0;
};

#endif