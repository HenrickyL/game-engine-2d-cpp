#ifndef GL_FRUSTUM_H
#define GL_FRUSTUM_H

#include "FrustumPlane.h"
#include "Position.h"
#include "Camera.h"
class Frustum {
private:
    FrustumPlane _planes[6];
    glm::vec4 _origin;
    glm::vec3 _nearPlaneVertices[4]; // Vértices do plano near
    glm::vec3 _farPlaneVertices[4];  // Vértices do plano far

public:
    ~Frustum() = default;
    void Update(const Camera& camera);
    void Update(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);

    bool IsInFrustum(const glm::vec3& position, float radius) const;

    glm::vec4 GetPlanePositions(int index) const;
    const glm::vec3* nearPlaneVertices() const;
    const glm::vec3* farPlaneVertices() const;
};

#endif