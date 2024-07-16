#include "Test2d.h"





void Test2D::Reset() {
}


void Test2D::Init() {
	window->SetColor(Color::GRAY);
	geo = new Rect(Position(0,0,0), 0.5,1, Color::RED);
	geometries.push_back(geo);
}
void Test2D::Update(double frameTime) {
	//glLoadIdentity();
	//glTranslatef(0, 0, 0);
	//gluLookAt(0.0, 0.0, 5.0,  // Posição da câmera (eye)
	//	0.0, 0.0, 0.0, // Ponto para onde a câmera está olhando (center)
	//	0.0, 1.0, 0.0); // Vetor "up" que define a orientação da câmera (up)
}


void Test2D::Draw() {
	for (Geometry* g : geometries) {
		_drawnner.Draw(*g);
	}
	
}
void Test2D::Finalize() {
	for (Geometry* g : geometries) {
		delete g;
	}
}