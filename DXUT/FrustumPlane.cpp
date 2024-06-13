#include "FrustumPlane.h"

FrustumPlane::FrustumPlane(float a, float b, float c, float d) : _normal(a, b, c, d) {}

FrustumPlane::FrustumPlane() : _normal(0.0f, 0.0f, 0.0f, 0.0f) {}

float FrustumPlane::DistanceToPoint(const glm::vec3& point) const {
    return glm::dot(glm::vec3(_normal), point) + _normal.w;
}

glm::vec4 FrustumPlane::normal() const {
    return _normal;
}
