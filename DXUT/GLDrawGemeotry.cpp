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


void GLDrawGeometry::Draw(const Geometry& geometry){
    glPushMatrix(); //local
        Color c = geometry.GetColor();
        glColor3f(c.r(), c.g(), c.b());

        glTranslatef(geometry.x(), geometry.y(), geometry.z());
        glRotatef(geometry.rotateAngle(), geometry.xRot(), geometry.yRot(), geometry.zRot());

	    if (const Rect* rect = dynamic_cast<const Rect*>(&geometry)) {
		    DrawRect(*rect);
        }
        else if (const Point* point = dynamic_cast<const Point*>(&geometry)) {
            DrawPoint(*point);
        }
    glPopMatrix();

}