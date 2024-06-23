#include "FrustumPlane.h"

FrustumPlane::FrustumPlane(float a, float b, float c, float d) : _normal(a, b, c, d) {
    _normal = glm::normalize(_normal);
}

FrustumPlane::FrustumPlane() : _normal(0.0f, 0.0f, 0.0f, 0.0f) {}

FrustumPlane::FrustumPlane(const glm::vec3& normal, const glm::vec3& point) {
    _normal = glm::vec4(normal, -glm::dot(normal, point));
}

float FrustumPlane::DistanceToPoint(const glm::vec3& point) const {
    return glm::dot(glm::vec3(_normal), point) + _normal.w;
}


glm::vec4 FrustumPlane::normal() const {
    return _normal;
}


void FrustumPlane::Normalize() {
    float length = glm::length(glm::vec3(_normal));
    _normal /= length;
}
