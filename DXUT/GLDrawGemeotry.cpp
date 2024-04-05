#include "GLDrawGeometry.h"
#include <iostream>

void GLDrawGeometry::DrawRect(const Rect& rect) {
    // Configurar a cor para o retângulo (vamos assumir vermelho para este exemplo)
    Color c = rect.GetColor();
    glColor3f(c.r(), c.g(), c.b()); // Vermelho

    glPushMatrix();
        glTranslatef(rect.x(), rect.y(), rect.z());
    
        // Desenhar o retângulo usando as coordenadas do mundo
        glBegin(GL_QUADS);
        glVertex3f(rect.Left(), rect.Top(), 0.0f); // Canto superior esquerdo
        glVertex3f(rect.Right(), rect.Top(), 0.0f); // Canto superior direito
        glVertex3f(rect.Right(), rect.Bottom(), 0.0f); // Canto inferior direito
        glVertex3f(rect.Left(), rect.Bottom(), 0.0f); // Canto inferior esquerdo
        glEnd();
        glTranslatef(-rect.x(), -rect.y(), -rect.z());
    glPopMatrix();
}

void GLDrawGeometry::Draw(const Geometry& geometry){
	if (const Rect* rect = dynamic_cast<const Rect*>(&geometry)) {
		DrawRect(*rect);
	}
}