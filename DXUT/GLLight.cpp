#include "GLLight.h"
#include <stdexcept>


int GLLight::_nextLightId = GL_LIGHT0;

void GLLight::_EnableGlobalLighting() {
    if (!_lightingEnabled) {
        glEnable(GL_LIGHTING);  // Habilitar iluminação global
        glEnable(GL_COLOR_MATERIAL); // TODO: use texture to
        glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
        //glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
        Light::_lightingEnabled = true;
    }
}

GLenum GLLight::_GenerateLightId() {
    if (_nextLightId > GL_LIGHT7) {
        throw std::runtime_error("Max Light in scene.");
    }
    return _nextLightId++;
}

//------------------------------------------------------------

GLLight::GLLight(float intensity, LightType type)
    : Light(intensity, type)
{
    _glLightId = _GenerateLightId();
    _EnableGlobalLighting();
}

GLLight::GLLight(const Vector& position, float intensity, LightType type)
    : Light(position, intensity, type)
{
    _glLightId = _GenerateLightId();
    _EnableGlobalLighting();
}

GLLight::GLLight(const Color& color, float intensity, LightType type)
    : Light(color, intensity, type)
{
    _glLightId = _GenerateLightId();
    _EnableGlobalLighting();
}

GLLight::GLLight(const Vector& position, const Color& color, float intensity, LightType type)
    : Light(position, color, intensity, type)
{
    _glLightId = _GenerateLightId();
    _EnableGlobalLighting();
}


//------------------------------------------------------------

void GLLight::Enable() {
    glEnable(_glLightId);
    Update();
}

void GLLight::Disable() {
    glDisable(_glLightId);
}

void GLLight::Update() {
    Vector dir = this->position();
    float x = dir.x();
    float y = dir.y();
    float z = dir.z();
    if (_type == L_POINT || _type == L_AMBIENT) {
        GLfloat position[] = { x, y, z, 1.0f};
        glLightfv(_glLightId, GL_POSITION, position);
    }
    else if (_type == L_DIRECTIONAL) {
        GLfloat direction[] = {x, y, z, 0.0f };
        glLightfv(_glLightId, GL_POSITION, direction);
    }

    // Configurar a cor e intensidade da luz no OpenGL
    float factor = 0.1f;
    float r = this->color().r();
    float g = this->color().g();
    float b = this->color().b();
    //Phong Model
    GLfloat ambient[] = { r* factor, g*factor, b * factor, 1.0f };
    glLightfv(_glLightId, GL_AMBIENT, ambient);
    
    GLfloat diffuse[] = { r * _intensity, g * _intensity, b * _intensity, 1.0f }; // L*M*cos
    glLightfv(_glLightId, GL_DIFFUSE, diffuse);
    
    GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //shininess(0-128)  | L * M * cos^(shininess)
    glLightfv(_glLightId, GL_SPECULAR, specular);

}