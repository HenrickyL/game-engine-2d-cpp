#include "GLOriginGizmoUI.h"
#include <GL/glew.h>


GLOriginGizmoUI::GLOriginGizmoUI(){}
GLOriginGizmoUI::GLOriginGizmoUI(int length) : OriginGizmoUI(length){}
GLOriginGizmoUI::GLOriginGizmoUI(const Position& pos, int length) : OriginGizmoUI(pos, length) {}

 

void GLOriginGizmoUI::InitBuffers() {
   
}

void GLOriginGizmoUI::Draw() {
    const float* origin = this->position().p3f();
    glLineWidth(_stroke);
    //glEnable(GL_LINE_SMOOTH); //antialising
    glBegin(GL_LINES);
        // Eixo X (vermelho)
        glColor3fv(_axisX.c3f());
        glVertex3fv(origin);
        glVertex3f(_length, 0.0f, 0.0f);
        // Eixo Y (verde)
        glColor3fv(_axisY.c3f());
        glVertex3fv(origin);
        glVertex3f(0.0f, _length, 0.0f);
        // Eixo Z (azul)
        glColor3fv(_axisZ.c3f());
        glVertex3fv(origin);
        glVertex3f(0.0f, 0.0f, _length);
    glEnd();
    //glDisable(GL_LINE_SMOOTH);

}