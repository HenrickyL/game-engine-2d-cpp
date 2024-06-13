#include "Frustum.h"
#include <array>

// Função auxiliar para criar um plano do frustum a partir de uma normal e um ponto
FrustumPlane FrustumPlaneFromNormalAndPoint(const glm::vec3& normal, const glm::vec4& point) {
    glm::vec3 normalizedNormal = glm::normalize(normal); // Normaliza a normal
    return FrustumPlane(normalizedNormal.x, normalizedNormal.y, normalizedNormal.z, -glm::dot(normalizedNormal, glm::vec3(point)));
}




void Frustum::Update(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) {
    glm::mat4 invProjMatrix = glm::inverse(projectionMatrix);
    glm::mat4 invViewMatrix = glm::inverse(viewMatrix);


    std::array<glm::vec4, 8> ndcPoints = {
        glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f), // near bottom left
        glm::vec4(1.0f, -1.0f, -1.0f, 1.0f),  // near bottom right
        glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f),  // near top left
        glm::vec4(1.0f, 1.0f, -1.0f, 1.0f),   // near top right
        glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f),  // far bottom left
        glm::vec4(1.0f, -1.0f, 1.0f, 1.0f),   // far bottom right
        glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f),   // far top left
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)     // far top right
    };

    // Transformar pontos do NDC para o espaço do mundo
    for (glm::vec4& point : ndcPoints) {
        point = invProjMatrix * point;
        point /= point.w; // Perspectiva divide
        point = invViewMatrix * point;
    }


    // Calcula os planos do frustum com base nos pontos transformados
    _planes[0] = FrustumPlaneFromNormalAndPoint(glm::cross(glm::vec3(ndcPoints[2] - ndcPoints[0]), glm::vec3(ndcPoints[1] - ndcPoints[0])), ndcPoints[0]); // Near plane
    _planes[1] = FrustumPlaneFromNormalAndPoint(glm::cross(glm::vec3(ndcPoints[6] - ndcPoints[4]), glm::vec3(ndcPoints[5] - ndcPoints[4])), ndcPoints[4]); // Far plane
    _planes[2] = FrustumPlaneFromNormalAndPoint(glm::cross(glm::vec3(ndcPoints[4] - ndcPoints[0]), glm::vec3(ndcPoints[2] - ndcPoints[0])), ndcPoints[0]); // Left plane
    _planes[3] = FrustumPlaneFromNormalAndPoint(glm::cross(glm::vec3(ndcPoints[7] - ndcPoints[3]), glm::vec3(ndcPoints[1] - ndcPoints[3])), ndcPoints[3]); // Right plane
    _planes[4] = FrustumPlaneFromNormalAndPoint(glm::cross(glm::vec3(ndcPoints[1] - ndcPoints[0]), glm::vec3(ndcPoints[3] - ndcPoints[0])), ndcPoints[0]); // Bottom plane
    _planes[5] = FrustumPlaneFromNormalAndPoint(glm::cross(glm::vec3(ndcPoints[3] - ndcPoints[2]), glm::vec3(ndcPoints[6] - ndcPoints[2])), ndcPoints[2]); // Top plane


    // Armazena os vértices dos planos near e far
    _nearPlaneVertices[0] = glm::vec3(ndcPoints[0]); // near bottom left
    _nearPlaneVertices[1] = glm::vec3(ndcPoints[1]); // near bottom right
    _nearPlaneVertices[2] = glm::vec3(ndcPoints[2]); // near top left
    _nearPlaneVertices[3] = glm::vec3(ndcPoints[3]); // near top right

    _farPlaneVertices[0] = glm::vec3(ndcPoints[4]);  // far bottom left
    _farPlaneVertices[1] = glm::vec3(ndcPoints[5]);  // far bottom right
    _farPlaneVertices[2] = glm::vec3(ndcPoints[6]);  // far top left
    _farPlaneVertices[3] = glm::vec3(ndcPoints[7]);  // far top right
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