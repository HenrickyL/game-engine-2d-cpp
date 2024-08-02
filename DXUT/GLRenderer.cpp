#include "GLRenderer.h"
#include <iostream>

void GLRenderer::DrawRect(const Rect& rect) const {
    float halfWidth = rect.Width() / 2;
    float halfHeight = rect.Height() / 2;

    glBegin(GL_QUADS);
        glVertex2f(-halfWidth, -halfHeight);
        glVertex2f(halfWidth, -halfHeight);
        glVertex2f(halfWidth, halfHeight);
        glVertex2f(-halfWidth, halfHeight);
    glEnd();
}

void GLRenderer::DrawPoint(const Point& point)const {
    glPointSize(point.Size());
    glBegin(GL_POINTS);
        glVertex3f(0,0,0);
    glEnd();

}

void GLRenderer::DrawLine(const Line& line)const {
    glLineWidth(line.Stroke());
    Point a = line.A();
    Point b = line.B();

    float dx = std::abs(a.x() - b.x())/2;
    float dy = std::abs(a.y() - b.y())/2;
    

    glBegin(GL_LINES);
        glVertex2f(-dx, -dy);
        glVertex2f(dx, dy);
    glEnd();
}


void GLRenderer::DrawCircle(const Circle& circle)const {
    GLfloat x, y, angle;
    float radius = circle.Radius();
    if (circle.isFilled()) {
        // Desenha um círculo preenchido
        glBegin(GL_TRIANGLE_FAN);
        // Desenha pontos ao redor do centro para formar o círculo
        for (angle = 0.0f; angle <= (2.0f * M_PI); angle += circle.OffSet()) {
            x = radius * sin(angle);
            y = radius * cos(angle);
            glVertex3f(x, y, .0f);
        }
        glVertex3f(.0f, .0f, .0f);
        glEnd();
    }
    else {
        glLineWidth(circle.Stroke());
        //glPointSize
        glBegin(GL_LINE_LOOP);
        for (angle = 0.0f; angle <= (2.0f * M_PI); angle += circle.OffSet())
        {
            x = circle.Radius() * sin(angle);
            y = circle.Radius() * cos(angle);
            glVertex3f(x, y, 0.0f);
        }
        glEnd();
    }
}

void GLRenderer::DrawPolygon(const Poly& polygon)const {
    if (polygon.isFilled()) {
        glBegin(GL_TRIANGLE_FAN);
        glBegin(GL_LINE_LOOP);
        for (const Point p : polygon.vertexList()) {
            glVertex3f(p.x(), p.y(), p.z());
        }
        glEnd();
    }
    else {
        glLineWidth(polygon.Stroke());
        glBegin(GL_LINE_LOOP);
            for (const Point p : polygon.vertexList()) {
                glVertex3f(p.x(), p.y(), p.z());
            }
        glEnd();
    }
}

void GLRenderer::SwitchTypeGeometryToDraw(const Geometry& geometry) const {
    if (const Rect* rect = dynamic_cast<const Rect*>(&geometry)) {
        this->DrawRect(*rect);
    }
    else if (const Point* point = dynamic_cast<const Point*>(&geometry)) {
        this->DrawPoint(*point);
    }
    else if (const Line* line = dynamic_cast<const Line*>(&geometry)) {
        this->DrawLine(*line);
    }
    else if (const Circle* circle = dynamic_cast<const Circle*>(&geometry)) {
        this->DrawCircle(*circle);
    }
    else if (const Poly* polygon = dynamic_cast<const Poly*>(&geometry)) {
        this->DrawPolygon(*polygon);
    }
}


void GLRenderer::Draw(const Geometry& geometry){
    glPushMatrix(); //local
        Color c = geometry.color();
        glColor3f(c.r(), c.g(), c.b());
        glTranslatef(geometry.x(), geometry.y(), geometry.z());
        glRotatef(geometry.xRot(), 1, 0, 0);
        glRotatef(geometry.yRot(), 0, 1, 0);
        glRotatef(geometry.zRot(), 0, 0, 1);

        SwitchTypeGeometryToDraw(geometry);
	    
    glPopMatrix();
}



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
    glScalef(scale*sprite.scales.x(), scale*sprite.scales.y(), 1.0f);
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