#ifndef GL_FRUSTUM_PLANE_H
#define GL_FRUSTUM_PLANE_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class FrustumPlane {
public:
    glm::vec4 _normal; // a, b, c, d components

    FrustumPlane();
    FrustumPlane(float a, float b, float c, float d);
    FrustumPlane(const glm::vec3& normal, const glm::vec3& point);


    float DistanceToPoint(const glm::vec3& point) const;

    glm::vec4 normal() const;
    void Normalize(); // Adiciona método para normalizar a normal
};



#endif