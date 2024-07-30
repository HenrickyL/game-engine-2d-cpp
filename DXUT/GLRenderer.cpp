#include "GLRenderer.h"
#include <iostream>

void GLRenderer::DrawRect(const Rect& rect) const {
    glBegin(GL_QUADS);
        glVertex3f(rect.Left(), rect.Top(), 0.0f); 
        glVertex3f(rect.Right(), rect.Top(), 0.0f);
        glVertex3f(rect.Right(), rect.Bottom(), 0.0f);
        glVertex3f(rect.Left(), rect.Bottom(), 0.0f);
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
        glRotatef(geometry.xRot(), 1,0,0);
        glRotatef(geometry.yRot(), 0, 1, 0);
        glRotatef(geometry.zRot(), 0, 0, 1);

        SwitchTypeGeometryToDraw(geometry);
	    
    glPopMatrix();
}


//TODO - Ver a diferença do pipeline com o GLRenderer (RenderBase::Render)
void GLRenderer::Draw(SpriteData& sprite) {
    GLImage* image = dynamic_cast<GLImage*>(sprite.image);
    float x = sprite.position.x();
    float y = sprite.position.y();
    float width = image->width();
    float height = image->height();

    if (!image) return;

    GLuint textureID = image->TextureID();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(x, y);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(x + width, y);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(x + width, y + height);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y + height);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}
