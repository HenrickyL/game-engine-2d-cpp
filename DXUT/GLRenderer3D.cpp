#include "GLRenderer3D.h"


void GLRenderer3D::Draw(const Shape3D& shape) {
    glPushMatrix(); // Save the current matrix
    Color c = shape.color();
    glColor3f(c.r(), c.g(), c.b());
    glTranslatef(shape.x(), shape.y(), shape.z());
    glRotatef(shape.rotateAngle(), shape.xRot(), shape.yRot(), shape.zRot());

    DrawShape(shape);

    glPopMatrix(); // Restore the matrix
}



class Renderer3D : public RendererBase {
private:
    virtual void DrawShape(const Shape3D& shape) const = 0;

public:
    virtual void Draw(const Shape3D& shape) = 0;
};

