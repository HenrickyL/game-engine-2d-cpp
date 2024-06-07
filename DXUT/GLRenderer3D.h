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
    void DrawShape(const Shape3D& shape) const override;
    void Pipeline(const Shape3D& shape) const;
public:
    void Draw(const Shape3D& shape) override;

    /* the methods below need the GLDrawableBase to be dynamically allocated */

    // Add  GLDrawableBase to Draw and Start Draw method in Display list to OpenGL
    void AddToDisplayList(GLDrawableBase* item);
    // remove  GLDrawableBase to draw
    void RemoveToDisplayList(GLDrawableBase* item);
    // Draw  Call Displaylist for Draw all GLDrawableBase
    void DrawDisplayList() const;
};
#endif
