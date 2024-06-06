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



void GLRenderer3D::DrawShape(const Shape3D& shape) const {
    vector<Vertex> vertices = shape.vertices();
    vector<Triangle> triangles = shape.triangles();

    Color c = shape.color();

    if (shape.isFlatColor()) {
        glColor3f(c.r(), c.g(), c.b());
    }

    if (_fillMode == F_SOLID || _fillMode == F_WIREFRAME_SOLID) {
        for (const Triangle& triangle : triangles) {
            glBegin(GL_TRIANGLES);
            // Loop through each vertex in the triangle and draw it
            for (int i = 0; i < 3; ++i) {
                const Vertex& vertex = triangle.vertices[i];
                glColor3f(vertex.r(), vertex.g(), vertex.b());
                glVertex3f(vertex.position.x(), vertex.position.y(), vertex.position.z());
            }
            glEnd();
        }
    }

    if (_fillMode == F_WIREFRAME || _fillMode == F_WIREFRAME_SOLID) {
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

    if (_fillMode == F_POINTS) {
        glColor3f(c.r(), c.g(), c.b());
        glPointSize(2.5f);
        glBegin(GL_POINTS);
        for (int i = 0; i < vertices.size(); i++) {
            Vertex v = vertices[i];
            if (!shape.isFlatColor()) {
                glColor3f(v.r(), v.g(), v.b());
            }
            glVertex3f(v.x(), v.y(), v.z());
        }
        glEnd();
    }
}


