#include "Frustum.h"
#include <array>

// Função auxiliar para criar um plano do frustum a partir de uma normal e um ponto
FrustumPlane FrustumPlaneFromNormalAndPoint(const glm::vec3& normal, const glm::vec4& point) {
    glm::vec3 normalizedNormal = glm::normalize(normal); // Normaliza a normal
    return FrustumPlane(normalizedNormal.x, normalizedNormal.y, normalizedNormal.z, -glm::dot(normalizedNormal, glm::vec3(point)));
}
void Frustum::Update(const Camera& camera) {
    // Obter posição e direção da câmera
    glm::vec3 pos = glm::vec3(camera.position().x(), camera.position().y(), camera.position().z());
    glm::vec3 dir = glm::normalize(glm::vec3(camera.direction().x(), camera.direction().y(), camera.direction().z()));
    glm::vec3 up = glm::normalize(glm::vec3(camera.orientation().x(), camera.orientation().y(), camera.orientation().z()));
    glm::vec3 right = glm::normalize(glm::cross(dir, up));

    // Obter FOV, aspect ratio, e distâncias dos planos near e far
    float fov = glm::radians(camera.fov());
    float aspectRatio = camera.aspect();
    float nearPlane = camera.zNear();
    float farPlane = camera.zFar();

    // Altura e largura dos planos near e far
    float tanFovHalf = tan(fov / 2.0f);
    float nearHeight = tanFovHalf * nearPlane * 2.0f;
    float nearWidth = nearHeight * aspectRatio;
    float farHeight = tanFovHalf * farPlane * 2.0f;
    float farWidth = farHeight * aspectRatio;

    // Centro dos planos near e far
    glm::vec3 nearCenter = pos + dir * nearPlane;
    glm::vec3 farCenter = pos + dir * farPlane;

    // Vértices dos planos near e far
    _nearPlaneVertices[0] = nearCenter - right * (nearWidth / 2) - up * (nearHeight / 2); // bottom left
    _nearPlaneVertices[1] = nearCenter + right * (nearWidth / 2) - up * (nearHeight / 2); // bottom right
    _nearPlaneVertices[2] = nearCenter + right * (nearWidth / 2) + up * (nearHeight / 2); // top right
    _nearPlaneVertices[3] = nearCenter - right * (nearWidth / 2) + up * (nearHeight / 2); // top left

    _farPlaneVertices[0] = farCenter - right * (farWidth / 2) - up * (farHeight / 2); // bottom left
    _farPlaneVertices[1] = farCenter + right * (farWidth / 2) - up * (farHeight / 2); // bottom right
    _farPlaneVertices[2] = farCenter + right * (farWidth / 2) + up * (farHeight / 2); // top right
    _farPlaneVertices[3] = farCenter - right * (farWidth / 2) + up * (farHeight / 2); // top left

    // Cálculo dos planos do frustum usando os vértices calculados
    _planes[0] = FrustumPlaneFromNormalAndPoint(-dir, glm::vec4(_nearPlaneVertices[0], 1.0f)); // Near plane
    _planes[1] = FrustumPlaneFromNormalAndPoint(dir, glm::vec4(_farPlaneVertices[0], 1.0f));   // Far plane
    _planes[2] = FrustumPlaneFromNormalAndPoint(-right, glm::vec4(_nearPlaneVertices[0], 1.0f)); // Left plane
    _planes[3] = FrustumPlaneFromNormalAndPoint(right, glm::vec4(_nearPlaneVertices[1], 1.0f));  // Right plane
    _planes[4] = FrustumPlaneFromNormalAndPoint(up, glm::vec4(_nearPlaneVertices[3], 1.0f));     // Top plane
    _planes[5] = FrustumPlaneFromNormalAndPoint(-up, glm::vec4(_nearPlaneVertices[0], 1.0f));   // Bottom plane
}


FrustumPlane PlaneFromPoints(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c) {
    glm::vec3 normal = glm::normalize(glm::cross(b - a, c - a));
    return FrustumPlane(normal, a);
}

/*

void Frustum::Update(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) {
    glm::mat4 invProjMatrix = glm::inverse(projectionMatrix);
    glm::mat4 invViewMatrix = glm::inverse(viewMatrix);


    std::array<glm::vec4, 8> ndcPoints = {
        glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f), // 0 near bottom left
        glm::vec4(1.0f, -1.0f, 1.0f, 1.0f),  // 1 near bottom right
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),   // 3 near top right
        glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f),  // 2 near top left
        glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f),  // 4 far bottom left
        glm::vec4(1.0f, -1.0f, -1.0f, 1.0f),   // 5 far bottom right
        glm::vec4(1.0f, 1.0f, -1.0f, 1.0f),     // 7 far top right
        glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f)   // 6 far top left
    };

    //std::array<glm::vec4, 8> ndcPoints = {
    //    glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f), // near bottom left
    //    glm::vec4(1.0f, -1.0f, -1.0f, 1.0f),  // near bottom right
    //    glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f),  // near top left
    //    glm::vec4(1.0f, 1.0f, -1.0f, 1.0f),   // near top right
    //    glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f),  // far bottom left
    //    glm::vec4(1.0f, -1.0f, 1.0f, 1.0f),   // far bottom right
    //    glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f),   // far top left
    //    glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)     // far top right
    //};

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


*/


void Frustum::Update(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) {
    glm::mat4 invProjViewMatrix = glm::inverse(projectionMatrix * viewMatrix);
    
    // Transform the origin of the frustum (camera position) correctly
    glm::vec4 origin = invProjViewMatrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    _origin = origin / origin.w;

    //Normalized Device Coordinates
    std::array<glm::vec4, 8> ndcPoints = {
        glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f),    // 0 near bottom left 
        glm::vec4(1.0f, -1.0f, 1.0f, 1.0f),     // 1 near bottom right
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),      // 2 near top right
        glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f),     // 3 near top left
        glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f),   // 4 far bottom left
        glm::vec4(1.0f, -1.0f, -1.0f, 1.0f),    // 5 far bottom right
        glm::vec4(1.0f, 1.0f, -1.0f, 1.0f),     // 6 far top right
        glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f)     // 7 far top left
    };

    for (glm::vec4& point : ndcPoints) {
        point = invProjViewMatrix * point;
        point /= point.w; // Perspectiva divide
    }


    // Calcula os planos do frustum com base nos pontos transformados
    //                                A             B             C
    _planes[0] = PlaneFromPoints(ndcPoints[0], ndcPoints[1], ndcPoints[2]); // Near plane
    _planes[1] = PlaneFromPoints(ndcPoints[4], ndcPoints[6], ndcPoints[5]); // Far plane
    _planes[2] = PlaneFromPoints(ndcPoints[0], ndcPoints[4], ndcPoints[7]); // Left plane
    _planes[3] = PlaneFromPoints(ndcPoints[1], ndcPoints[5], ndcPoints[6]); // Right plane
    _planes[4] = PlaneFromPoints(ndcPoints[0], ndcPoints[4], ndcPoints[5]); // Bottom plane
    _planes[5] = PlaneFromPoints(ndcPoints[3], ndcPoints[6], ndcPoints[7]); // Top plane


    // Armazena os vértices dos planos near e far
    _nearPlaneVertices[0] = glm::vec3(ndcPoints[0]); // near bottom left
    _nearPlaneVertices[1] = glm::vec3(ndcPoints[1]); // near bottom right
    _nearPlaneVertices[2] = glm::vec3(ndcPoints[2]); // near top right
    _nearPlaneVertices[3] = glm::vec3(ndcPoints[3]); // near top left

    _farPlaneVertices[0] = glm::vec3(ndcPoints[4]);  // far bottom left
    _farPlaneVertices[1] = glm::vec3(ndcPoints[5]);  // far bottom right
    _farPlaneVertices[2] = glm::vec3(ndcPoints[6]);  // far top right
    _farPlaneVertices[3] = glm::vec3(ndcPoints[7]);  // far top left
}

bool Frustum::IsInFrustum(const glm::vec3& position, float radius) const {
    glm::vec3 origin = glm::vec3(_origin.x, _origin.y, _origin.z);
    for (const FrustumPlane& plane : _planes) {
        float e = abs(plane.DistanceToPoint(position - origin)); // relative to origin
        float d = abs(plane.DistanceToPoint(origin)); //distance plane to origin
        float x = e - d;
        if ( e-d > radius) {
            return false;
        }
    }
    return true;
}

//bool Frustum::IsInFrustum(const glm::vec3& position, float radius) const {
//    for (int i = 0; i < 6; ++i) {
//        if (_planes[i].DistanceToPoint(position) < -radius) {
//            return false;
//        }
//    }
//    return true;
//}

glm::vec4 Frustum::GetPlanePositions(int index) const {
    return _planes[index].normal();
}


const glm::vec3* Frustum::nearPlaneVertices() const { return _nearPlaneVertices; }
const glm::vec3* Frustum::farPlaneVertices() const { return _farPlaneVertices; }