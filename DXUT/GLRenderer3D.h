#ifndef UT_GL_RENDERER_3D_H
#define UT_GL_RENDERER_3D_H

#include "Renderer3D.h"
#include "GLDrawableBase.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
using std::vector;

class GLRenderer3D : public Renderer3D {
private:
    vector<GLDrawableBase> _listToDraw;

    void DrawShape(const Shape3D& shape) const override;
    void Pipeline(const Shape3D& shape) const;
public:
    void Draw(const Shape3D& shape) override;
};
#endif
