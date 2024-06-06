#include "GLRenderer3D.h"


void GLRenderer3D::Draw(const Shape3D& shape) {
    glPushMatrix(); // Save the current matrix
    Color c = shape.color();
    glColor3f(c.r(), c.g(), c.b());
    glTranslatef(shape.x(), shape.y(), shape.z());
    glRotatef(shape.rotateAngle(), shape.xRot(), shape.yRot(), shape.zRot());

    SwitchTypShapeToDraw(shape);

    glPopMatrix(); // Restore the matrix
}

void GLRenderer3D::SwitchTypShapeToDraw(const Shape3D& shape) const
{
    if (const Cube* cube = dynamic_cast<const Cube*>(&shape)) {
        this->DrawCube(*cube);
    }
    else if (const Sphere* sphere = dynamic_cast<const Sphere*>(&shape)) {
        this->DrawSphere(*sphere);
    }
}



void GLRenderer3D::DrawCube(const Cube& cube) const {
    
    vector<Vertex> vertices = cube.vertices();

    // Definir as faces do cubo
    int faces[6][4] = {
        { 0, 1, 2, 3 }, // Frente
        { 3, 2, 5, 4 }, // Direita
        { 4, 5, 6, 7 }, // Traseira
        { 7, 6, 1, 0 }, // Esquerda
        { 1, 6, 5, 2 }, // Inferior
        { 0, 3, 4, 7 }  // Superior
    };
    Color faceColors[6] = {
        Color::RED,
        Color::BLUE,
        Color::GREEN,
        Color::YELLOW,
        Color::MAGENTA,
        Color::WHITE,
    };

    

    // Desenhar os quadrados
    if (_fillMode == F_SOLID || _fillMode == F_WIREFRAME_SOLID) {
        glBegin(GL_QUADS);
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 4; ++j) {
                int vertexIndex = faces[i][j];
                if (!cube.isFlatColor()) {
                    Color c = faceColors[i];
                    glColor3f(c.r(), c.g(), c.b());
                }
                Vertex vertex = vertices[vertexIndex];
                glVertex3f(vertex.x(), vertex.y(), vertex.z());
            }
        }
        glEnd();
    }

    // Desenhar as linhas
    if (_fillMode == F_WIREFRAME || _fillMode == F_WIREFRAME_SOLID) {
        Color c = cube.color();
        if (_fillMode == F_WIREFRAME_SOLID) {
            Color lineColor = c.Brightness(0.2);
            glColor3f(lineColor.r(), lineColor.g(), lineColor.b());
        }
        glBegin(GL_LINES);
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 4; ++j) {
                int vertexIndex1 = faces[i][j];
                int vertexIndex2 = faces[i][(j + 1) % 4];
                Vertex vertex = vertices[vertexIndex1];
                glVertex3f(vertex.x(), vertex.y(), vertex.z());
                vertex = vertices[vertexIndex2];
                glVertex3f(vertex.x(), vertex.y(), vertex.z());
            }
        }
        glEnd();
        if (_fillMode == F_WIREFRAME_SOLID) {
            glColor3f(c.r(), c.g(), c.b());
        }
    }

    // Desenhar os pontos
    if (_fillMode == F_POINTS) {
        glPointSize(3);
        glBegin(GL_POINTS);
        for (int i = 0; i < 8; ++i) {
            Vertex vertex = vertices[i];
            glVertex3f(vertex.x(), vertex.y(), vertex.z());
        }
        glEnd();
    }
}



void GLRenderer3D::DrawSphere(const Sphere& shape) const {

    vector<Vertex> vertices = shape.vertices();

    
    //draw
    Color c = shape.color();
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


