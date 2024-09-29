#include "Light.h"

bool Light::_lightingEnabled = false;

void Light::_EnableLighting() {
	Light::_lightingEnabled = true;
}


Light::Light(float intensity, LightType type)
	: Movable(Vector::Zero), Colored(Color::WHITE), _intensity(intensity), _type(type)
{}
Light::Light(const Vector& position, float intensity, LightType type) 
	: Movable(position), Colored(Color::WHITE), _intensity(intensity), _type(type)
{}
Light::Light(const Color& color, float intensity, LightType type) 
	: Movable(Vector::Zero), Colored(color), _intensity(intensity), _type(type) {}
Light::Light(const Vector& position, const Color& color, float intensity, LightType type) 
	: Movable(position), Colored(color), _intensity(intensity), _type(type) {}

float Light::intensity() const { return _intensity; }
void Light::SetIntensity(float intensity) { _intensity = intensity; }
LightType Light::type() const { return _type; }
void Light::SetType(LightType type) { _type = type; }