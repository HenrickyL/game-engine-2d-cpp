#ifndef UT_GL_LIGHT_H
#define UT_GL_LIGHT_H

#include "Light.h"
#include <GLFW/glfw3.h>

class GLLight : public Light {
private:
    GLenum _glLightId;                  // ID da luz OpenGL (GL_LIGHT0, GL_LIGHT1...)
    static int _nextLightId;

    static void _EnableGlobalLighting();
    GLenum _GenerateLightId();

public:
    // Construtor
    GLLight(float intensity, LightType type = L_AMBIENT);
    GLLight(const Vector& position, float intensity, LightType type = L_AMBIENT);
    GLLight(const Color& color, float intensity, LightType type = L_AMBIENT);
    GLLight(const Vector& position, const Color& color, float intensity, LightType type = L_AMBIENT);

    // Métodos herdados de Light
    void Enable() override;
    void Disable() override;
    void Update() override;
};

#endif // UT_GL_LIGHT_H
