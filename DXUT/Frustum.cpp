#include "Frustum.h"

void Frustum::Update(const Camera& camera) {
	Position pos = camera.position();
	glm::vec3 cameraPos = glm::vec3(pos.x(), pos.y(), pos.z());
	Vector _direction = camera.direction();
	Vector _orientation = camera.orientation();
	Vector _left = camera.left();

	// Calcula os vértices da base do frustum (near plane)
	float halfHeight = tan(glm::radians(camera.frustumFov() / 2.0f)) * camera.frustumNear();
	float halfWidth = halfHeight * camera.frustumAspect();
	glm::vec3 dir = glm::vec3(_direction.x(), _direction.y(), _direction.z());
	glm::vec3 ori = glm::vec3(_orientation.x(), _orientation.y(), _orientation.z());
	glm::vec3 left = glm::vec3(_left.x(), _left.y(), _left.z());


	glm::vec3 centerNear = cameraPos + dir * camera.frustumNear();
	glm::vec3 topLeftNear = centerNear + (ori * halfHeight) - (left * halfWidth);
	glm::vec3 topRightNear = centerNear + (ori * halfHeight) + (left * halfWidth);
	glm::vec3 bottomLeftNear = centerNear - (ori * halfHeight) - (left * halfWidth);
	glm::vec3 bottomRightNear = centerNear - (ori * halfHeight) + (left * halfWidth);

	// Calcula os vértices da base do frustum (far plane)
	float halfHeightFar = tan(glm::radians(camera.frustumFov() / 2.0f)) * camera.frustumFar();
	float halfWidthFar = halfHeightFar * camera.frustumAspect();
	glm::vec3 centerFar = cameraPos + dir * camera.frustumFar();
	glm::vec3 topLeftFar = centerFar + (ori * halfHeightFar) - (left * halfWidthFar);
	glm::vec3 topRightFar = centerFar + (ori * halfHeightFar) + (left * halfWidthFar);
	glm::vec3 bottomLeftFar = centerFar - (ori * halfHeightFar) - (left * halfWidthFar);
	glm::vec3 bottomRightFar = centerFar - (ori * halfHeightFar) + (left * halfWidthFar);

	// Armazena os vértices dos planos near e far
	_nearPlaneVertices[0] = topLeftNear;
	_nearPlaneVertices[1] = topRightNear;
	_nearPlaneVertices[2] = bottomRightNear;
	_nearPlaneVertices[3] = bottomLeftNear;

	_farPlaneVertices[0] = topLeftFar;
	_farPlaneVertices[1] = topRightFar;
	_farPlaneVertices[2] = bottomRightFar;
	_farPlaneVertices[3] = bottomLeftFar;

	// Calcular os planos do frustum usando os vértices
	glm::vec3 nearNormal = glm::normalize(glm::cross(_nearPlaneVertices[1] - _nearPlaneVertices[0], _nearPlaneVertices[3] - _nearPlaneVertices[0]));
	glm::vec3 farNormal = glm::normalize(glm::cross(_farPlaneVertices[1] - _farPlaneVertices[0], _farPlaneVertices[3] - _farPlaneVertices[0]));

	_planes[0] = FrustumPlane(nearNormal.x, nearNormal.y, nearNormal.z, glm::dot(nearNormal, _nearPlaneVertices[0])); // Near plane
	_planes[1] = FrustumPlane(farNormal.x, farNormal.y, farNormal.z, glm::dot(farNormal, _farPlaneVertices[0])); // Far plane

	// Calcular planos laterais, superior e inferior
	glm::vec3 leftNormal = glm::normalize(glm::cross(_nearPlaneVertices[0] - _farPlaneVertices[0], _farPlaneVertices[3] - _farPlaneVertices[0]));
	glm::vec3 rightNormal = glm::normalize(glm::cross(_nearPlaneVertices[1] - _farPlaneVertices[1], _farPlaneVertices[2] - _farPlaneVertices[1]));
	glm::vec3 bottomNormal = glm::normalize(glm::cross(_nearPlaneVertices[3] - _farPlaneVertices[3], _farPlaneVertices[2] - _farPlaneVertices[3]));
	glm::vec3 topNormal = glm::normalize(glm::cross(_nearPlaneVertices[0] - _farPlaneVertices[0], _farPlaneVertices[1] - _farPlaneVertices[0]));

	_planes[2] = FrustumPlane(leftNormal.x, leftNormal.y, leftNormal.z, glm::dot(leftNormal, _farPlaneVertices[0])); // Left plane
	_planes[3] = FrustumPlane(rightNormal.x, rightNormal.y, rightNormal.z, glm::dot(rightNormal, _farPlaneVertices[1])); // Right plane
	_planes[4] = FrustumPlane(bottomNormal.x, bottomNormal.y, bottomNormal.z, glm::dot(bottomNormal, _farPlaneVertices[3])); // Bottom plane
	_planes[5] = FrustumPlane(topNormal.x, topNormal.y, topNormal.z, glm::dot(topNormal, _farPlaneVertices[0])); // Top plane
}

bool Frustum::IsInFrustum(const glm::vec3& position, float radius) const {
    for (int i = 0; i < 6; ++i) {
        if (_planes[i].DistanceToPoint(position) < -radius) {
            return false;
        }
    }
    return true;
}

glm::vec4 Frustum::GetPlanePositions(int index) const {
    return _planes[index].normal();
}


const glm::vec3* Frustum::nearPlaneVertices() const { return _nearPlaneVertices; }
const glm::vec3* Frustum::farPlaneVertices() const { return _farPlaneVertices; }