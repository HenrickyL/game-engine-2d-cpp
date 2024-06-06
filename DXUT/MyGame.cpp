#include "MyGame.h"

#include "Engine.h" 



void drawTriangle(Obj pos) {
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(pos.x, pos.y + 0.5, pos.z);
	glVertex3f(pos.x + 0.5, pos.y - 0.5, pos.z);
	glVertex3f(pos.x - 0.5, pos.y - 0.5, pos.z);
	glEnd();
}

void drawQuad(Obj pos) {
	glColor3f(1.f, 0.f, 0.f);
	glBegin(GL_QUADS);
	glVertex3f(pos.x - 2.5, pos.y - 2.5, pos.z);
	glVertex3f(pos.x + 2.5, pos.y - 2.5, pos.z);
	glVertex3f(pos.x + 2.5, pos.y + 2.5, pos.z);
	glVertex3f(pos.x - 2.5, pos.y + 2.5, pos.z);
	glEnd();
}


void DrawRect(float p1[3], float p2[3], float p3[3], float p4[3], Color c) {
	float cs[3] = { c.r(), c.g(), c.b() };
	glColor3fv(cs);
	glBegin(GL_QUADS);
	glVertex3fv(p1);
	glVertex3fv(p2);
	glVertex3fv(p3);
	glVertex3fv(p4);
	glEnd();
}

void drawCube(Position pos, float size = 2.5f) {
	float d = size / 2;
	glColor3f(1.f, 0.f, 0.f);
	float v1[3] = { pos.x() - d,		pos.y() + d,	pos.z() + d };
	float v2[3] = { pos.x() - d,			pos.y() - d,		pos.z() + d };
	float v3[3] = { pos.x() + d,		pos.y() - d,		pos.z() + d };
	float v4[3] = { pos.x() + d,		pos.y() + d,		pos.z() + d };
	float v5[3] = { pos.x() + d,		pos.y() + d,		pos.z() - d };
	float v6[3] = { pos.x() + d,		pos.y() - d,		pos.z() - d };
	float v7[3] = { pos.x() - d,			pos.y() - d,		pos.z() - d };
	float v8[3] = { pos.x() - d,			pos.y() + d,		pos.z() - d };


	//frente
	DrawRect(v1, v2, v3, v4, Color::RED);

	DrawRect(v4, v3, v6, v5, Color::BLUE);

	DrawRect(v5, v8, v7, v6, Color::GREEN);

	DrawRect(v1, v8, v7, v2, Color::YELLOW);

	DrawRect(v1, v4, v5, v8, Color::MAGENTA);

	DrawRect(v2, v7, v6, v3, Color::WHITE);

}//-----------------------------------------------------------------------------





void MyGame::Init() {
	window = Engine::window;

	/*GLCamera cam1(Position(0, 0, 5));
	GLCamera cam2(Position(0, 0, 5));*/

	cam = new GLCamera(Position(0, 0, 5));


	bool onMode = true;

	
	int index = 0;

	functionVector.push_back(drawQuad);
	functionVector.push_back(drawTriangle);

	
	Rect r(Position(0, 0, 0), 1, 1);
	Rect r2(Position(-0.5, 0, 0), 1, 1);
	Rect r3(Position(0.5, 0, 0), 1, 1);

	rect = new Rect(Position::Zero, 1, 1);

	Rect rects[3] = { r, r2, r3 };

	Rect selected = r;
	r.RotationZ(1);
	
	Point p;
	p.setSize(1);

	Line l(Position(-1, 0), Position(1, 0.5));
	l.setStroke(5);

	Circle c = Circle(Position(1, 0), 1);
	c.setStroke(3);


	Poly poly;
	poly.setStroke(3);
	poly.addVertex(Position(0, 0.5));
	poly.addVertex(Position(0.5, -0.5));
	poly.addVertex(Position(-0.5, -0.5));

	obj = rect;

	Point center = Point(obj->position());
	center.setSize(10);

	object = cam; 
	cube.SetColor(Color::GRAY);
	_drawnner.SetFillMode(F_WIREFRAME_SOLID);
	sphere.SetIsFlatColor(true);
	sphere.generateVertices();
}
void MyGame::Update(double frameTime){


	if (Input::KeyPress(KEY_G)) {
		MyGame::window->isResizeable(true);
	}

	if (Input::KeyDown(KEY_A)) {
		globalRotation -= frameTime*10;
	}

	if (Input::KeyDown(KEY_D)) {
		globalRotation += frameTime * 10;
	}

	if (Input::KeyDown(LEFT)) {
		object->TranslateTo(Vector::Left * frameTime);
	}
	if (Input::KeyDown(RIGHT) ) {
		object->TranslateTo(Vector::Right * frameTime);

	}
	if (Input::KeyDown(UP) ) {
		object->TranslateTo(Vector::Backward * frameTime);

	}
	if (Input::KeyDown(DOWN)) {
		object->TranslateTo(Vector::Forward * frameTime);
	}

	if (Input::OnDrag() ) {
		Position mp = Input::MousePosition();
		float x = mp.x();
		float y = mp.y();

		Position current = Position(x - window->Width() / 2, y - window->Height() / 2);

		Vector d = Position::Zero - current;
		if (d.Magnitude() != 0)
			cam->TranslateLookAt(d.Unit() * frameTime);
	}


	if (Input::OnWheel()) {
		int dir = Input::MouseWheelDirection();
		if (dir != 0)
			object->TranslateTo((dir > 0 ? Vector::Up : Vector::Down) );
	}


	if (Input::KeyPress(KEY_T)) {
		onSolid = (onSolid+1)%4;
		_drawnner.SetFillMode((FillModeEnum)onSolid);
	}



	if (Input::KeyPress(SPACE)) {
		index++;
		if (index >= functionVector.size()) {
			index = 0;
		}
	}

	glLoadIdentity();
	cam->Update();
	/*int count = 0;
	while (count < 8000000) { count++; }*/


	glTranslatef(0, 0, 0);
	glRotatef(globalRotation, 0, 0, 1);

}

void MyGame::Draw(){
	//drawner.Draw(*obj);
	//drawCube(Position::Zero);
	_drawnner.Draw(sphere);
}

void MyGame::Finalize(){
	delete cam;
	delete rect;

}

