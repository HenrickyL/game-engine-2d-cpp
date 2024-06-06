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
    float halfWidth = cube.width() / 2;
    float halfHeight = cube.height() / 2;
    float halfDepth = cube.depth() / 2;

    // Definir os vértices do cubo
    std::vector<Position> vertices = {
        Position(-halfWidth, halfHeight, halfDepth),   // v1
        Position(-halfWidth, -halfHeight, halfDepth),  // v2
        Position(halfWidth, -halfHeight, halfDepth),   // v3
        Position(halfWidth, halfHeight, halfDepth),    // v4
        Position(halfWidth, halfHeight, -halfDepth),   // v5
        Position(halfWidth, -halfHeight, -halfDepth),  // v6
        Position(-halfWidth, -halfHeight, -halfDepth), // v7
        Position(-halfWidth, halfHeight, -halfDepth)   // v8
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
                glVertex3f(vertices[vertexIndex].x(), vertices[vertexIndex].y(), vertices[vertexIndex].z());
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
                glVertex3f(vertices[vertexIndex1].x(), vertices[vertexIndex1].y(), vertices[vertexIndex1].z());
                glVertex3f(vertices[vertexIndex2].x(), vertices[vertexIndex2].y(), vertices[vertexIndex2].z());
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
            glVertex3f(vertices[i].x(), vertices[i].y(), vertices[i].z());
        }
        glEnd();
    }
}



void GLRenderer3D::DrawSphere(const Sphere& shape) const {
    //generate Vertex
    float phi; // -pi/2 - pi/2
    float theta; //0 - 2pi
    const float PI = 3.14159265359;

    int nStack = shape.stacks();
    int nSector = shape.sectors();
    int radius = shape.radius();

    vector<Position> vertices;
    vector<Color> verticesColor;

    
    float deltaPhi = PI / nStack;
    float deltaTheta = 2 * PI / nSector;


    for (int i = 0; i <= nStack; i++) {
        phi = -PI / 2.0 + i * deltaPhi;
        float temp = radius * cos(phi);
        float y = radius * sin(phi);
        for (int j = 0; j < nSector; j++) {
            theta = j * deltaTheta;
            float x = temp * sin(theta);
            float z = temp * cos(theta);
            vertices.push_back(Position(x, y, z));
            verticesColor.push_back(Color::RandomColor());
        }
    }
    //draw
    Color c = shape.color();
    glColor3f(c.r(), c.g(), c.b());
    glPointSize(2.5f);
    glBegin(GL_POINTS);
    for (int i = 0; i < vertices.size(); i++) {
        if (!shape.isFlatColor()) {
            Color c = verticesColor[i];
            glColor3f(c.r(), c.g(), c.b());
        }
        glVertex3f(vertices[i].x(), vertices[i].y(), vertices[i].z());
    }
    glEnd();
}


