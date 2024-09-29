#include "Test2d.h"





void Test2D::Reset() {
	geo->MoveTo(Position::Zero);
}


void Test2D::Init() {
	window->SetColor(Color::GRAY);

	img = new GLImage("Resources/player.png");
	sprite = new Sprite(img);
	sprite->MoveTo(Position(0,0));
	sprite->SetScales(Vector::One*0.3);

	_drawnner = new GLRenderer();

	float value = 0.3;
	geo = new Rect(Position(0.2, 0, -1), value, value, Color::RED);
	//geo->setFilled(false);
	geometries.push_back(geo);
}
void Test2D::Update(double frameTime) {
	//glTranslatef(0, 0, 0);
	//gluLookAt(0.0, 0.0, 5.0,  // Posição da câmera (eye)
	//	0.0, 0.0, 0.0, // Ponto para onde a câmera está olhando (center)
	//	0.0, 1.0, 0.0); // Vetor "up" que define a orientação da câmera (up)

	Vector dir = Vector::Left;
	if (Input::KeyDown(LEFT)){
		dir = Vector::Left;
		geo->TranslateTo(dir * frameTime);
		sprite->TranslateTo(dir * frameTime);
	}
	else if (Input::KeyDown(RIGHT)) {
		dir = Vector::Right;
		geo->TranslateTo(dir * frameTime);
		sprite->TranslateTo(dir * frameTime);
	}

	if (Input::KeyDown(UP)) {
		dir = Vector::Up;
		geo->TranslateTo(dir * frameTime);
		sprite->TranslateTo(dir * frameTime);
	}
	else if (Input::KeyDown(DOWN)) {
		dir = Vector::Down;
		geo->TranslateTo(dir * frameTime);
		sprite->TranslateTo(dir * frameTime);
	}

	if (Input::KeyDown(KEY_R)) {
		Reset();
	}

	if (Input::OnWheel()) {
		int orientation = Input::MouseWheelDirection();
		float delta = 3;
		Vector dir = Vector::Forward;
		if (orientation != 0) {
			Vector v = dir * delta * orientation;
			geo->RotateBy(v);
			sprite->RotateBy(v);

			if(Input::KeyDown(SHIFT_LEFT))
				sprite->TranslateTo(dir * 0.1 * orientation);
		}
	}

	if (Input::KeyDown(KEY_W)) {
		Color c = geo->color();
		geo->SetColor(Color(c.r(), c.g(), c.b(), c.a() + 0.1));
	}else if (Input::KeyDown(KEY_S)) {
		Color c = geo->color();
		geo->SetColor(Color(c.r(), c.g(), c.b(), c.a() - 0.1));
	}


	glLoadIdentity();


	glTranslatef(0, 0, 0);
	glRotatef(globalRotation.x(), 1, 0, 0);
	glRotatef(globalRotation.y(), 0, 1, 0);
	glRotatef(globalRotation.z(), 0, 0, 1);
}


void Test2D::Draw() {
	for (Geometry* g : geometries) {
		_drawnner->Draw(*g);
	}
	SpriteData* data = sprite->data();
	_drawnner->Draw(*data);
	
}
void Test2D::Finalize() {
	for (Geometry* g : geometries) {
		delete g;
	}
	if (img) delete img;
}