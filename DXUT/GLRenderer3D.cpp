#include "GLRenderer3D.h"


void GLRenderer3D::Draw(const Shape3D& shape) {
    glPushMatrix(); // Save the current matrix
        glTranslatef(shape.x(), shape.y(), shape.z());
        glRotatef(shape.xRot(), 1,0,0);
        glRotatef(shape.yRot(), 0,1,0);
        glRotatef(shape.zRot(), 0,0,1);


        Pipeline(shape);

    glPopMatrix(); // Restore the matrix
}

void GLRenderer3D::Pipeline(const Shape3D& shape) const {
    glLineWidth(1.0f);
    glPointSize(1.0f);
    switch (_fillMode)
    {
    case F_WIREFRAME:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(1.2f);
        break;
    case F_POINTS:
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        glPointSize(2.5f);
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

    const float* c = shape.color().c4f();
    
    if (shape.isFlatColor()) {
        glColor4fv(c);
    }

    for (const Triangle& triangle : triangles) {
        glBegin(GL_TRIANGLES);
        for (int i = 0; i < 3; ++i) {
            const Vertex& vertex = triangle.vertices[i];
            if (!shape.isFlatColor()) {
                glColor4fv(vertex.color.c4f());
            }
            glVertex3fv(vertex.position.p3f());
        }
        glEnd();
    }

    if (_fillMode == F_WIREFRAME_SOLID) {
        glColor4fv(c);
        glLineWidth(1.2f);
        //glEnable(GL_LINE_SMOOTH); //antialising

        for (const Triangle& triangle : triangles) {
            glBegin(GL_LINE_LOOP);
            for (int i = 0; i < 3; ++i) {
                const Vertex& vertex = triangle.vertices[i];
                Color lineColor = vertex.color;
                if (_fillMode == F_WIREFRAME_SOLID) {
                    lineColor = vertex.color.Brightness(0.2);
                }
                glColor3fv(lineColor.c4f());
                glVertex3fv(vertex.position.p3f());
            }
            glEnd();
        }
        //glDisable(GL_LINE_SMOOTH);
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
    item->Init();
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
