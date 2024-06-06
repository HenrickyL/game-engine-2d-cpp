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
}



void GLRenderer3D::DrawCube(const Cube& cube) const {
    float halfWidth = cube.width() / 2;
    float halfHeight = cube.height() / 2;
    float halfDepth = cube.depth() / 2;

    // Definir os vértices do cubo
    float vertices[8][3] = {
        { -halfWidth, halfHeight, halfDepth },    // v1
        { -halfWidth, -halfHeight, halfDepth },   // v2
        { halfWidth, -halfHeight, halfDepth },    // v3
        { halfWidth, halfHeight, halfDepth },     // v4
        { halfWidth, halfHeight, -halfDepth },    // v5
        { halfWidth, -halfHeight, -halfDepth },   // v6
        { -halfWidth, -halfHeight, -halfDepth }, // v7
        { -halfWidth, halfHeight, -halfDepth }   // v8
    };

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
                glVertex3f(vertices[vertexIndex][0], vertices[vertexIndex][1], vertices[vertexIndex][2]);
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
                glVertex3f(vertices[vertexIndex1][0], vertices[vertexIndex1][1], vertices[vertexIndex1][2]);
                glVertex3f(vertices[vertexIndex2][0], vertices[vertexIndex2][1], vertices[vertexIndex2][2]);
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
            glVertex3f(vertices[i][0], vertices[i][1], vertices[i][2]);
        }
        glEnd();
    }

    

    
}

