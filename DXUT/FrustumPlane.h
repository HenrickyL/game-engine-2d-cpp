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

    float DistanceToPoint(const glm::vec3& point) const;

    glm::vec4 normal() const;
};



#endif