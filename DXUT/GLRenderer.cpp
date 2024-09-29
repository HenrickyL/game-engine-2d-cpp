#include "GLRenderer.h"
#include "GLVertexBufferID.h"
#include "GLImage.h"

#include "GLShader.h"

const char* vertexShaderSource = R"(
    #version 330 core
    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec4 aColor;

    out vec4 vertexColor;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main() {
        gl_Position = projection * view * model * vec4(aPos, 1.0);
        vertexColor = aColor;
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core
    in vec4 vertexColor;

    out vec4 FragColor;

    void main() {
        FragColor = vertexColor;
    }
)";



// *************************************************************************************************

GLRenderer::GLRenderer(const GLCamera* camera) : _camera(camera) {
    EnableCulling();
    SetPolygonModeFill(true);
} 
void GLRenderer::InitializeShader() {
    //GLuint _shaderProgram;
    this->_shaderProgram = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
}


GLRenderer::~GLRenderer() {
    //// Limpeza dos buffers
    //if (_vao) glDeleteVertexArrays(1, &_vao);
    //if (_vbo) glDeleteBuffers(1, &_vbo);
    //if (_ebo) glDeleteBuffers(1, &_ebo);
}





void GLRenderer::Draw(Mesh& shape) {
    glPushMatrix(); // Save the current matrix
        glTranslatef(shape.x(), shape.y(), shape.z());
        glRotatef(shape.xRot(), 1,0,0);
        glRotatef(shape.yRot(), 0,1,0);
        glRotatef(shape.zRot(), 0,0,1);


        Pipeline(shape);

    glPopMatrix(); // Restore the matrix
}


void GLRenderer::UpdateShape(Mesh& shape) {
    if (shape.isDirty()) {
        this->Initialize(shape);
        shape.Clear(); // Limpa o estado sujo após a atualização
    }
}


void GLRenderer::Render(Mesh& shape) {
    this->UpdateShape(shape);
    GLVertexBufferID* glId = dynamic_cast<GLVertexBufferID*>(shape.id());
    if (glId == nullptr)
        return;

    glBindVertexArray(glId->vao());

    // Configura o VBO de posição
    glBindBuffer(GL_ARRAY_BUFFER, glId->vboPosition());
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, nullptr);

    // Configura o VBO de cor
    glBindBuffer(GL_ARRAY_BUFFER, glId->vboColor());
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(4, GL_FLOAT, 0, nullptr);

    // Desenha os elementos
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glId->ebo());
    glDrawElements(GL_TRIANGLES, shape.indices().size(), GL_UNSIGNED_INT, nullptr);

    // Limpeza das configurações
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindVertexArray(0);
}

bool GLRenderer::IsValidToDraw(Mesh& shape) const {
    return !_camera || !_camera->IsInFrustum(shape.position(), shape.boundingRadius());
}

void GLRenderer::Pipeline(Mesh& shape) {
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

    // TODO: Remove - Test use Frustum

    if (_camera && _camera->useFrustum()) {
        if (!IsValidToDraw(shape)) {
            shape.SetColor(Color::RED);
        }
        else {
            shape.SetColor(Color::YELLOW);
        }
    }
   

    if (_useVertexBuffer) {
        Render(shape);
    }
    else {
        DrawShape(shape);
    }
   
}

void GLRenderer::DrawVertex(const Mesh& shape, const Vertex& vertex)const {
    
    if (!shape.isFlatColor()) {
        glColor4fv(vertex.color.c4f());
    }
    glVertex3fv(vertex.position.p3f());
}

void GLRenderer::SetupIlumination() const{ //TODO: Use Material
    // Defina as propriedades do material
    GLfloat matSpecular[] = { 1.0, 1.0, 1.0, 1.0 };  // Exemplo de cor especular branca
    GLfloat shininess = 50.0f;  // Exemplo de valor de brilho

    // Define a cor especular e brilho do material
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}


void GLRenderer::DrawShape(const Mesh& shape) const {
    const vector<Vertex> vertices = shape.vertices();
    const vector<uint>& indices = shape.indices();
    const vector<Vector>& normals = shape.normals();

    this->SetupIlumination();

    const float* c = shape.color().c4f();
    
    if (shape.isFlatColor()) {
        glColor4fv(c);
    }

    glBegin(GL_TRIANGLES);
        for (size_t i = 0; i < indices.size(); i += 3) {
            if (normals.size() > 0) {
                const Vector& normal = normals[i / 3];
                glNormal3f(normal.x(), normal.y(), normal.z());
            }
            DrawVertex(shape, vertices[indices[i]]);
            DrawVertex(shape, vertices[indices[i+1]]);
            DrawVertex(shape, vertices[indices[i+2]]);
        }
    glEnd();

    this->_DrawWireframe(vertices, indices, c);
}

void GLRenderer::_DrawWireframe(const vector<Vertex> vertices, const vector<uint>& indices, const float* color) const {
    if (_fillMode == F_WIREFRAME_SOLID) {
        glColor4fv(color);
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



void GLRenderer::AddToDisplayList(GLDrawableBase* item) {
    this->addElement(item);
    item->Init();
    glNewList(item->id(), GL_COMPILE);
        item->Draw();
    glEndList();
}
void GLRenderer::RemoveToDisplayList(GLDrawableBase* item){
    this->removeElement(item);
}
void GLRenderer::DrawDisplayList() const{
    for (GLDrawableBase* item : _elements) {
        if (item->isDirty()) {
            glNewList(item->id(), GL_COMPILE);
                item->Draw();
            glEndList();
            item->Clear();
        }
        glCallList(item->id());
    }
}

void GLRenderer::DeleteVS(Mesh& shape) {
    GLVertexBufferID* glId = dynamic_cast<GLVertexBufferID*>(shape.id());
    if (glId != nullptr) {
        uint _vao = glId->vao();
        uint _vboPosition = glId->vboPosition();
        uint _vboColor = glId->vboColor();
        uint _ebo = glId->ebo();

        // Deleta o VAO, VBOs e EBO
        glDeleteVertexArrays(1, &_vao);
        glDeleteBuffers(1, &_vboPosition);
        glDeleteBuffers(1, &_vboColor);
        glDeleteBuffers(1, &_ebo);

        // Reseta os identificadores no GLVertexBufferID
        glId->SetVao(0);
        glId->SetVboPosition(0);
        glId->SetVboColor(0);
        glId->SetEbo(0);
    }
}



void GLRenderer::Initialize(Mesh& shape){
    // Inicializa os shaders
    InitializeShader();

    // Verifica se o Shape3D possui um objeto GLVertexBufferID válido
    GLVertexBufferID* glId = dynamic_cast<GLVertexBufferID*>(shape.id());
    if (glId == nullptr) {
        // Se não houver um GLVertexBufferID, cria um e associa ao Shape3D
        glId = new GLVertexBufferID();
        shape.SetId(glId);
    }

    // Obtém os identificadores do VAO, VBO para posição, VBO para cor e EBO do GLVertexBufferID
    uint _vao = glId->vao();
    uint _vboPosition = glId->vboPosition();
    uint _vboColor = glId->vboColor();
    uint _ebo = glId->ebo();

    // Gera os buffers VAO, VBOs e EBO
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vboPosition);
    glGenBuffers(1, &_vboColor);
    glGenBuffers(1, &_ebo);

    // Gerar e bindar VAO
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
    // Gerar e bindar VBO para posição
    glGenBuffers(1, &_vboPosition);
    glBindBuffer(GL_ARRAY_BUFFER, _vboPosition);
    glBufferData(GL_ARRAY_BUFFER, shape.vertices().size() * 3 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

    // Preencher VBO de posição
    float* positionBufferData = static_cast<float*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
    if (positionBufferData) {
        size_t offset = 0;
        for (const Vertex& vertex : shape.vertices()) {
            const Position& pos = vertex.position;
            positionBufferData[offset++] = pos.x();
            positionBufferData[offset++] = pos.y();
            positionBufferData[offset++] = pos.z();
        }
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }

    // Gerar e bindar VBO para cor
    glGenBuffers(1, &_vboColor);
    glBindBuffer(GL_ARRAY_BUFFER, _vboColor);
    glBufferData(GL_ARRAY_BUFFER, shape.vertices().size() * 4 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

    // Preencher VBO de cor
    float* colorBufferData = static_cast<float*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
    if (colorBufferData) {
        size_t offset = 0;
        for (const Vertex& vertex : shape.vertices()) {
            
            const Color& col = shape.isFlatColor() ? shape.color() : vertex.color;
            colorBufferData[offset++] = col.r();
            colorBufferData[offset++] = col.g();
            colorBufferData[offset++] = col.b();
            colorBufferData[offset++] = col.a();
        }
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }

    // Gerar e bindar EBO
    glGenBuffers(1, &_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    // Aloca memória para os dados de índice no EBO e preenche com os dados dos índices
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.indices().size() * sizeof(unsigned int), shape.indices().data(), GL_DYNAMIC_DRAW);

    // Configuração dos atributos de vértice

    // Atributo posição
    glBindBuffer(GL_ARRAY_BUFFER, _vboPosition);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Atributo cor
    glBindBuffer(GL_ARRAY_BUFFER, _vboColor);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Desvincula o VAO para evitar modificações acidentais
    glBindVertexArray(0);

    // Armazena os identificadores atualizados no GLVertexBufferID
    glId->SetVao(_vao);
    glId->SetVboPosition(_vboPosition);
    glId->SetVboColor(_vboColor);
    glId->SetEbo(_ebo);
}


void GLRenderer::EnableCulling() {
    glEnable(GL_CULL_FACE);// Habilita o culling de faces para melhorar a performance.
    glFrontFace(GL_CCW);// Define a orientação das faces frontais como contrárias ao sentido
    glCullFace(GL_BACK);// Especifica que as faces traseiras devem ser descartadas.
}
void GLRenderer::DisableCulling(){
    glDisable(GL_CULL_FACE);
}
void GLRenderer::SetPolygonModeFill(bool value){
    if (value) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // GL_LINE é geralmente o padrão para glPolygonMode.
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


/*   SPRITES  */

//TODO - Ver a diferença do pipeline com o GLRenderer (RenderBase::Render)
void GLRenderer::Draw(SpriteData& sprite) {
    if (!sprite.image) return;
    GLImage* image = dynamic_cast<GLImage*>(sprite.image);
    if (!image) return;
    GLuint textureID = image->TextureID();
    if (textureID == 0) return;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Verificar erros do OpenGL antes de desenhar
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        throw std::runtime_error("Any Error");
    }

    glColor4fv(sprite.color.c4f());

    glPushMatrix(); // Save the current matrix

        ApplyTransformations(sprite);
        ApplyTextureTransformations(sprite);

        DrawQuad(sprite);

        ResetTextureTransformations();

    glPopMatrix(); // Restore the matrix

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void GLRenderer::ApplyTransformations(const SpriteData& sprite) {
    float x = sprite.position.x();
    float y = sprite.position.y();
    float value = 1 - sprite.position.z();
    float scale = value < 0 ? 0 : value;

    glTranslatef(x, y, sprite.depth);
    glRotatef(sprite.rotation.z(), 0, 0, 1);
    glScalef(scale * sprite.scales.x(), scale * sprite.scales.y(), 1.0f);
}

void GLRenderer::ApplyTextureTransformations(const SpriteData& sprite) {
    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    glLoadIdentity();

    //// Mova o centro da textura para (0.5, 0.5)
    //glTranslatef(0.5f, 0.5f, 0.0f);
    //// Aplique a rotação em torno do eixo z
    ////glRotatef(sprite.rotation.z(), 0.0f, 0.0f, 1.0f);
    //// Mova de volta para a posição original
    //glTranslatef(-0.5f, -0.5f, 0.0f);

    glMatrixMode(GL_MODELVIEW);
}

void GLRenderer::ResetTextureTransformations() {
    glMatrixMode(GL_TEXTURE);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void GLRenderer::DrawQuad(const SpriteData& sprite) {
    float halfWidth = sprite.width / 2;
    float halfHeight = sprite.height / 2;

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-halfWidth, -halfHeight);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(halfWidth, -halfHeight);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(halfWidth, halfHeight);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-halfWidth, halfHeight);
    glEnd();
}