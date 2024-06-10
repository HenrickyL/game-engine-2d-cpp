#ifndef UT_GL_METHODS_H
#define UT_GL_METHODS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// Definição das matrizes de transformação
glm::mat4 modelMatrix;      // Matriz de transformação do modelo
glm::mat4 viewMatrix;       // Matriz de transformação da visão
glm::mat4 projectionMatrix; // Matriz de transformação da projeção

// Função para inicializar as matrizes de visualização e projeção
void InitMatrices() {
    // Defina a matriz de visualização para a posição e orientação da câmera
    viewMatrix = glm::lookAt(cameraPosition, cameraTarget, cameraUp);

    // Defina a matriz de projeção para aplicar perspectiva ou projeção ortográfica
    projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

// Função para atualizar os uniformes de matrizes no shader
void UpdateMatrixUniforms(GLuint shaderProgram) {
    // Obtenha os IDs dos uniformes no shader
    GLuint modelMatrixUniform = glGetUniformLocation(shaderProgram, "model");
    GLuint viewMatrixUniform = glGetUniformLocation(shaderProgram, "view");
    GLuint projectionMatrixUniform = glGetUniformLocation(shaderProgram, "projection");

    // Atualize os uniformes com as matrizes correspondentes
    glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}

// Função para renderizar um objeto
void RenderObject(Shape3D& shape) {
    // Atualize a matriz de modelo com as transformações locais do objeto
    modelMatrix = calculateModelMatrix(shape);

    // Atualize os uniformes de matrizes no shader
    UpdateMatrixUniforms(shaderProgram);

    // Renderize o objeto
    Render(shape);
}

// Função para inicializar os shaders e as matrizes de transformação
void InitShadersAndMatrices() {
    // Inicialize os shaders
    InitShaders();

    // Inicialize as matrizes de transformação
    InitMatrices();
}

// Função de inicialização do programa
void Initialize() {
    // Inicialize os shaders e as matrizes de transformação
    InitShadersAndMatrices();
}

// Função de renderização
void Render() {
    // Limpe o buffer de cor e de profundidade
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Renderize cada objeto da cena
    for (Shape3D& shape : sceneObjects) {
        RenderObject(shape);
    }

    // Troque os buffers (double buffering)
    glutSwapBuffers();
}

// Função de atualização da cena (por exemplo, para animações)
void Update() {
    // Atualize as matrizes de transformação, se necessário
    UpdateMatricesIfNeeded();

    // Solicite uma nova renderização
    glutPostRedisplay();
}



#endif