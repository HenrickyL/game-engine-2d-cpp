#include "GLRenderer3D.h"

GLRenderer3D::~GLRenderer3D() {
    // Limpeza dos buffers
    if (_vao) glDeleteVertexArrays(1, &_vao);
    if (_vbo) glDeleteBuffers(1, &_vbo);
    if (_ebo) glDeleteBuffers(1, &_ebo);
}




void GLRenderer3D::Draw(Shape3D& shape) {
    glPushMatrix(); // Save the current matrix
        glTranslatef(shape.x(), shape.y(), shape.z());
        glRotatef(shape.xRot(), 1,0,0);
        glRotatef(shape.yRot(), 0,1,0);
        glRotatef(shape.zRot(), 0,0,1);


        Pipeline(shape);

    glPopMatrix(); // Restore the matrix
}

void GLRenderer3D::Render(const Shape3D& shape) const {
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, shape.indices().size(), GL_UNSIGNED_INT, 0); // Usando a quantidade correta de índices
    glBindVertexArray(0);
}



void GLRenderer3D::Pipeline(const Shape3D& shape) const {
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

    if (_useVertexBuffer) {
        Render(shape);
    }
    else {
        DrawShape(shape);
    }

    glDisable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void GLRenderer3D::DrawVertex(const Shape3D& shape, const Vertex& vertex)const {
    
    if (!shape.isFlatColor()) {
        glColor4fv(vertex.color.c4f());
    }
    glVertex3fv(vertex.position.p3f());
}


void GLRenderer3D::DrawShape(const Shape3D& shape) const {
    const vector<Vertex> vertices = shape.vertices();
    //vector<Triangle> triangles = shape.triangles();
    const vector<uint>& indices = shape.indices();

    const float* c = shape.color().c4f();
    
    if (shape.isFlatColor()) {
        glColor4fv(c);
    }

    glBegin(GL_TRIANGLES);
        for (size_t i = 0; i < indices.size(); i += 3) {
            DrawVertex(shape, vertices[indices[i]]);
            DrawVertex(shape, vertices[indices[i+1]]);
            DrawVertex(shape, vertices[indices[i+2]]);
        }
    glEnd();

    if (_fillMode == F_WIREFRAME_SOLID) {
        glColor4fv(c);
        glLineWidth(1.2f);
        for (size_t i = 0; i < indices.size(); i += 3) {
            glBegin(GL_LINE_LOOP);
            for (int j = 0; j < 3; j++) {
                const Vertex& vertex = vertices[indices[i + j]];
                Color lineColor = vertex.color;
                if (_fillMode == F_WIREFRAME_SOLID) {
                    lineColor = vertex.color.Brightness(0.2);
                }
                glColor3fv(lineColor.c4f());
                glVertex3fv(vertex.position.p3f());
            }
            glEnd();
        }
    }
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


void GLRenderer3D::Initialize(const Shape3D& shape){
    // 1. Geração do VAO, VBO e EBO
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_ebo);

    // 2. Bind do VAO
    glBindVertexArray(_vao);

    // 3. Bind do VBO e cópia dos dados dos vértices para ele
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    // Calcula o tamanho total dos dados dos vértices (posição + cor)
    size_t vertexDataSize = shape.vertices().size() * (sizeof(float) * 7); // 3 floats para posição + 4 floats para cor

    // Aloca memória para os dados do VBO
    glBufferData(GL_ARRAY_BUFFER, vertexDataSize, nullptr, GL_STATIC_DRAW);

    // Preenche o VBO com os dados de posição e cor
    float* vertexBufferData = static_cast<float*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
    if (vertexBufferData) {
        size_t vertexOffset = 0;
        for (const Vertex& vertex : shape.vertices()) {
            // Copia as coordenadas da posição
            const Position& pos = vertex.position;
            vertexBufferData[vertexOffset++] = pos.x();
            vertexBufferData[vertexOffset++] = pos.y();
            vertexBufferData[vertexOffset++] = pos.z();

            // Copia as componentes de cor
            const Color& col =shape.isFlatColor()? shape.color() : vertex.color;
            vertexBufferData[vertexOffset++] = col.r();
            vertexBufferData[vertexOffset++] = col.g();
            vertexBufferData[vertexOffset++] = col.b();
            vertexBufferData[vertexOffset++] = col.a();
        }
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }

    // 4. Bind do EBO e cópia dos dados dos índices para ele
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.indices().size() * sizeof(unsigned int), shape.indices().data(), GL_STATIC_DRAW);

    // 5. Configuração dos atributos de vértice
    // Atributo posição
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, nullptr);

    // Atributo cor
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)(sizeof(float) * 3)); // Offset de 3 floats (posição) para chegar às cores

    // 6. Desvinculação do VAO para evitar modificações acidentais
    glBindVertexArray(0);
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