#ifndef UT_GL_RENDERER_3D_H
#define UT_GL_RENDERER_3D_H

#include "Renderer3D.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLRenderer3D : public Renderer3D {
public:
    void Draw(const Shape3D& shape) override;
private:
    void DrawCube(const Cube& cube) const override;

    void SwitchTypShapeToDraw(const Shape3D& shape) const override;
};

#endif
