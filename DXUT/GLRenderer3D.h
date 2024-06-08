#ifndef UT_GL_RENDERER_3D_H
#define UT_GL_RENDERER_3D_H

#include "Renderer3D.h"
#include "GLDrawableBase.h"
#include "AbstractList.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
using std::vector;

class GLRenderer3D : public Renderer3D, public AbstractList<GLDrawableBase*> {
private:
    uint _vao = 0; // Vertex Array Object
    uint _vbo = 0; // Vertex Buffer Object
    uint _ebo = 0; // Element Buffer Object
    void DrawShape(const Shape3D& shape) const override;
    void Pipeline(const Shape3D& shape) const;
    void Initialize(const Shape3D& shape);
    void DrawVertex(const Shape3D& shape, const Vertex& vertex)const;

public:
    ~GLRenderer3D();
    void Draw(const Shape3D& shape) override;

    // Add  GLDrawableBase to Draw and Start Draw method in Display list to OpenGL
    void AddToDisplayList(GLDrawableBase* item);
    // remove  GLDrawableBase to draw
    void RemoveToDisplayList(GLDrawableBase* item);
    // Draw  Call Displaylist for Draw all GLDrawableBase
    void DrawDisplayList() const;

    //VAO - VBO
};
#endif
