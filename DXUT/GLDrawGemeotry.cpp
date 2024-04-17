#include "GLDrawGeometry.h"
#include <iostream>

void GLDrawGeometry::DrawRect(const Rect& rect) const {
    glBegin(GL_QUADS);
        glVertex3f(rect.Left(), rect.Top(), 0.0f); 
        glVertex3f(rect.Right(), rect.Top(), 0.0f);
        glVertex3f(rect.Right(), rect.Bottom(), 0.0f);
        glVertex3f(rect.Left(), rect.Bottom(), 0.0f);
    glEnd();
}

void GLDrawGeometry::DrawPoint(const Point& point)const {
    glPointSize(point.Size());
    glBegin(GL_POINTS);
        glVertex3f(0,0,0);
    glEnd();

}

void GLDrawGeometry::DrawLine(const Line& line)const {
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


void GLDrawGeometry::DrawCircle(const Circle& circle)const {
    GLfloat x, y, angle;
    glPointSize(circle.Stroke());
    glBegin(GL_POINTS);
    for (angle = 0.0f; angle <= (2.0f * M_PI); angle += circle.OffSet())
    {
        x = circle.Radius() * sin(angle);
        y = circle.Radius() * cos(angle);
        glVertex3f(x, y, 0.0f);
    }
    glEnd();

}




void GLDrawGeometry::Draw(const Geometry& geometry){
    glPushMatrix(); //local
        Color c = geometry.GetColor();
        glColor3f(c.r(), c.g(), c.b());

        glTranslatef(geometry.x(), geometry.y(), geometry.z());
        glRotatef(geometry.rotateAngle(), geometry.xRot(), geometry.yRot(), geometry.zRot());

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
    glPopMatrix();

}