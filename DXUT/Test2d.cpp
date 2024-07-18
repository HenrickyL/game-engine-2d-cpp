#include "Test2d.h"





void Test2D::Reset() {
	geo->MoveTo(Position::Zero);
}


void Test2D::Init() {
	window->SetColor(Color::GRAY);
	geo = new Rect(Position(0,0,0), 0.2,0.2, Color::RED);
	geo->setFilled(false);
	geometries.push_back(geo);
}
void Test2D::Update(double frameTime) {
	glLoadIdentity();
	//glTranslatef(0, 0, 0);
	//gluLookAt(0.0, 0.0, 5.0,  // Posição da câmera (eye)
	//	0.0, 0.0, 0.0, // Ponto para onde a câmera está olhando (center)
	//	0.0, 1.0, 0.0); // Vetor "up" que define a orientação da câmera (up)

	Vector dir = Vector::Left;
	if (Input::KeyDown(LEFT)){
		dir = Vector::Left;
		geo->TranslateTo(dir * frameTime);
	}
	else if (Input::KeyDown(RIGHT)) {
		dir = Vector::Right;
		geo->TranslateTo(dir * frameTime);
	}

	if (Input::KeyDown(UP)) {
		dir = Vector::Up;
		geo->TranslateTo(dir * frameTime);
	}
	else if (Input::KeyDown(DOWN)) {
		dir = Vector::Down;
		geo->TranslateTo(dir * frameTime);
	}

	if (Input::KeyDown(KEY_R)) {
		Reset();
	}
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