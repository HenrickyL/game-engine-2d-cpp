#ifndef UT_GL_RENDERER_3D_H
#define UT_GL_RENDERER_3D_H

#include "Renderer.h"
#include "GLDrawableBase.h"
#include "AbstractList.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "GLCamera.h"

using std::vector;

class GLRenderer : public Renderer, public AbstractList<GLDrawableBase*> {
private:
    const GLCamera* _camera = nullptr;
    //TODO: see RenderMethod
    /*
        * Color no changed
        * vertexPosition no changed
        * talvez precise de shaders
    */
    bool _useVertexBuffer = false;
    GLuint _shaderProgram;
    //uint _vao = 0; // Vertex Array Object
    //uint _vbo = 0; // Vertex Buffer Object
    //uint _ebo = 0; // Element Buffer Object
    void DrawShape(const Mesh& shape) const;
    void Pipeline(Mesh& shape);
    void DrawVertex(const Mesh& shape, const Vertex& vertex)const;
    void DeleteVS(Mesh& shape);
    void UpdateShape(Mesh& shape);


    void EnableCulling();
    void DisableCulling();
    void SetPolygonModeFill(bool value);

    bool IsValidToDraw(Mesh& shape) const;
    void InitializeShader();

    //sprites
    void ApplyTransformations(const SpriteData& sprite);
    void ApplyTextureTransformations(const SpriteData& sprite);
    void ResetTextureTransformations();
    void DrawQuad(const SpriteData& sprite);

public:
    GLRenderer(const GLCamera* camera = nullptr);
    ~GLRenderer();
    void Draw(Mesh& shape) override;
    void Draw(SpriteData& sprite) override;


    //vertexBuffer
    void Initialize(Mesh& shape);
    void Render(Mesh& shape);


    //DisplayList
    // Add  GLDrawableBase to Draw and Start Draw method in Display list to OpenGL
    void AddToDisplayList(GLDrawableBase* item);
    // remove  GLDrawableBase to draw
    void RemoveToDisplayList(GLDrawableBase* item);
    // Draw  Call Displaylist for Draw all GLDrawableBase
    void DrawDisplayList() const;
};
#endif
