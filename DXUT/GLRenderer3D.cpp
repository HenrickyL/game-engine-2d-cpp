#include "GLRenderer3D.h"


void GLRenderer3D::Draw(const Shape3D& shape) {
    glPushMatrix(); // Save the current matrix
    Color c = shape.color();
    glColor3f(c.r(), c.g(), c.b());
    glTranslatef(shape.x(), shape.y(), shape.z());
    glRotatef(shape.rotateAngle(), shape.xRot(), shape.yRot(), shape.zRot());

    Pipeline(shape);

    glPopMatrix(); // Restore the matrix
}

void GLRenderer3D::Pipeline(const Shape3D& shape) const {
    switch (_fillMode)
    {
    case F_WIREFRAME:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        break;
    case F_POINTS:
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        break;
    default:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        break;
    }

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    DrawShape(shape);

    glDisable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void GLRenderer3D::DrawShape(const Shape3D& shape) const {
    vector<Vertex> vertices = shape.vertices();
    vector<Triangle> triangles = shape.triangles();

    Color c = shape.color();
    
    if (shape.isFlatColor()) {
        glColor3f(c.r(), c.g(), c.b());
    }

    for (const Triangle& triangle : triangles) {
        glBegin(GL_TRIANGLES);
        for (int i = 0; i < 3; ++i) {
            const Vertex& vertex = triangle.vertices[i];
            glColor3f(vertex.r(), vertex.g(), vertex.b());
            glVertex3f(vertex.position.x(), vertex.position.y(), vertex.position.z());
        }
        glEnd();
    }

    if (_fillMode == F_WIREFRAME_SOLID) {
        glColor3f(c.r(), c.g(), c.b());
        glLineWidth(1.2f);
        for (const Triangle& triangle : triangles) {
            glBegin(GL_LINE_LOOP);
            for (int i = 0; i < 3; ++i) {
                const Vertex& vertex = triangle.vertices[i];
                Color lineColor = vertex.color;
                if (_fillMode == F_WIREFRAME_SOLID) {
                    lineColor = vertex.color.Brightness(0.2);
                }
                glColor3f(lineColor.r(), lineColor.g(), lineColor.b());
                glVertex3f(vertex.position.x(), vertex.position.y(), vertex.position.z());
            }
            glEnd();
        }
    }

    //if (_fillMode == F_POINTS) {
    //    glColor3f(c.r(), c.g(), c.b());
    //    glPointSize(2.5f);
    //    glBegin(GL_POINTS);
    //    for (int i = 0; i < vertices.size(); i++) {
    //        Vertex v = vertices[i];
    //        if (!shape.isFlatColor()) {
    //            glColor3f(v.r(), v.g(), v.b());
    //        }
    //        glVertex3f(v.x(), v.y(), v.z());
    //    }
    //    glEnd();
    //}
    

}


void GLRenderer3D::AddToDisplayList(GLDrawableBase* item) {
    this->addElement(item);
    item->init();
    glNewList(item->id(), GL_COMPILE);
        item->Draw();
    glEndList();
}
void GLRenderer3D::RemoveToDisplayList(GLDrawableBase* item){
    this->removeElement(item);
}
void GLRenderer3D::DrawDisplayList() const{
    for (GLDrawableBase* item : _elements) {
        glCallList(item->id());
    }
}
